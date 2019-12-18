#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mask; scalar_t__* area; scalar_t__ id; } ;
struct TYPE_4__ {TYPE_1__ cartridge; scalar_t__* bram; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CART_BRAM ; 
 int /*<<< orphan*/  CD_BRAM_EU ; 
 int /*<<< orphan*/  CD_BRAM_JP ; 
 int /*<<< orphan*/  CD_BRAM_US ; 
 int CHUNKSIZE ; 
#define  REGION_EUROPE 130 
#define  REGION_JAPAN_NTSC 129 
#define  REGION_USA 128 
 scalar_t__* brm_crc ; 
 int* brm_format ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fread (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (scalar_t__*,int*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int region_code ; 
 TYPE_2__ scd ; 

__attribute__((used)) static void bram_load(void)
{
    FILE *fp;

    /* automatically load internal backup RAM */
    switch (region_code)
    {
       case REGION_JAPAN_NTSC:
          fp = fopen(CD_BRAM_JP, "rb");
          break;
       case REGION_EUROPE:
          fp = fopen(CD_BRAM_EU, "rb");
          break;
       case REGION_USA:
          fp = fopen(CD_BRAM_US, "rb");
          break;
       default:
          return;
    }

    if (fp != NULL)
    {
      fread(scd.bram, 0x2000, 1, fp);
      fclose(fp);

      /* update CRC */
      brm_crc[0] = crc32(0, scd.bram, 0x2000);
    }
    else
    {
      /* force internal backup RAM format (does not use previous region backup RAM) */
      scd.bram[0x1fff] = 0;
    }

    /* check if internal backup RAM is correctly formatted */
    if (memcmp(scd.bram + 0x2000 - 0x20, brm_format + 0x20, 0x20))
    {
      /* clear internal backup RAM */
      memset(scd.bram, 0x00, 0x2000 - 0x40);

      /* internal Backup RAM size fields */
      brm_format[0x10] = brm_format[0x12] = brm_format[0x14] = brm_format[0x16] = 0x00;
      brm_format[0x11] = brm_format[0x13] = brm_format[0x15] = brm_format[0x17] = (sizeof(scd.bram) / 64) - 3;

      /* format internal backup RAM */
      memcpy(scd.bram + 0x2000 - 0x40, brm_format, 0x40);

      /* clear CRC to force file saving (in case previous region backup RAM was also formatted) */
      brm_crc[0] = 0;
    }

    /* automatically load cartridge backup RAM (if enabled) */
    if (scd.cartridge.id)
    {
      fp = fopen(CART_BRAM, "rb");
      if (fp != NULL)
      {
        int filesize = scd.cartridge.mask + 1;
        int done = 0;
        
        /* Read into buffer (2k blocks) */
        while (filesize > CHUNKSIZE)
        {
          fread(scd.cartridge.area + done, CHUNKSIZE, 1, fp);
          done += CHUNKSIZE;
          filesize -= CHUNKSIZE;
        }

        /* Read remaining bytes */
        if (filesize)
        {
          fread(scd.cartridge.area + done, filesize, 1, fp);
        }

        /* close file */
        fclose(fp);

        /* update CRC */
        brm_crc[1] = crc32(0, scd.cartridge.area, scd.cartridge.mask + 1);
      }

      /* check if cartridge backup RAM is correctly formatted */
      if (memcmp(scd.cartridge.area + scd.cartridge.mask + 1 - 0x20, brm_format + 0x20, 0x20))
      {
        /* clear cartridge backup RAM */
        memset(scd.cartridge.area, 0x00, scd.cartridge.mask + 1);

        /* Cartridge Backup RAM size fields */
        brm_format[0x10] = brm_format[0x12] = brm_format[0x14] = brm_format[0x16] = (((scd.cartridge.mask + 1) / 64) - 3) >> 8;
        brm_format[0x11] = brm_format[0x13] = brm_format[0x15] = brm_format[0x17] = (((scd.cartridge.mask + 1) / 64) - 3) & 0xff;

        /* format cartridge backup RAM */
        memcpy(scd.cartridge.area + scd.cartridge.mask + 1 - 0x40, brm_format, 0x40);
      }
    }
}