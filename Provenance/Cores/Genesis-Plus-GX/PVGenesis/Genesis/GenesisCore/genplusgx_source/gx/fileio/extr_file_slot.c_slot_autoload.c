#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int s_auto; } ;
struct TYPE_4__ {int mask; scalar_t__* area; scalar_t__ id; } ;
struct TYPE_5__ {TYPE_1__ cartridge; scalar_t__* bram; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CART_BRAM ; 
 int CHUNKSIZE ; 
 int SILENT ; 
 scalar_t__ SYSTEM_MCD ; 
 scalar_t__* brm_crc ; 
 int /*<<< orphan*/ * brm_filename ; 
 int* brm_format ; 
 TYPE_3__ config ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fread (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (scalar_t__*,int*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int region_code ; 
 int /*<<< orphan*/  rom_filename ; 
 TYPE_2__ scd ; 
 int /*<<< orphan*/  slot_load (int,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ system_hw ; 

void slot_autoload(int slot, int device)
{
  /* Mega CD backup RAM specific */
  if (!slot && (system_hw == SYSTEM_MCD))
  {
    /* automatically load internal backup RAM */
    FILE *fp = fopen(brm_filename[((region_code ^ 0x40) >> 6) - 1], "rb");
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

  /* configurable SRAM & State auto-saving */
  if ((slot && !(config.s_auto & 2)) || (!slot && !(config.s_auto & 1)))
  {
    return;
  }

  if (strlen(rom_filename))
  {  
    SILENT = 1;
    slot_load(slot, device);
    SILENT = 0;
  }
}