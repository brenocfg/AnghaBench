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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {int romsize; int /*<<< orphan*/  rom; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bootrom; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD_BIOS_EU ; 
 int /*<<< orphan*/  CD_BIOS_JP ; 
 int /*<<< orphan*/  CD_BIOS_US ; 
 int /*<<< orphan*/  GG_BIOS ; 
 int /*<<< orphan*/  MS_BIOS_EU ; 
 int /*<<< orphan*/  MS_BIOS_JP ; 
 int /*<<< orphan*/  MS_BIOS_US ; 
#define  REGION_EUROPE 134 
#define  REGION_USA 133 
#define  SYSTEM_GG 132 
#define  SYSTEM_GGMS 131 
#define  SYSTEM_MCD 130 
#define  SYSTEM_SMS 129 
#define  SYSTEM_SMS2 128 
 TYPE_2__ cart ; 
 int load_archive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int region_code ; 
 TYPE_1__ scd ; 
 int system_bios ; 
 int system_hw ; 

int load_bios(void)
{
  int size = 0;

  switch (system_hw)
  {
    case SYSTEM_MCD:
    {
      /* check if CD BOOTROM is already loaded */
      if (!(system_bios & 0x10) || ((system_bios & 0x0c) != (region_code >> 4)))
      {
        /* load CD BOOTROM (fixed 128KB size) */
        switch (region_code)
        {
          case REGION_USA:
            size = load_archive(CD_BIOS_US, scd.bootrom, sizeof(scd.bootrom), 0);
            break;
          case REGION_EUROPE:
            size = load_archive(CD_BIOS_EU, scd.bootrom, sizeof(scd.bootrom), 0);
            break;
          default:
            size = load_archive(CD_BIOS_JP, scd.bootrom, sizeof(scd.bootrom), 0);
            break;
        }

        /* CD BOOTROM loaded ? */
        if (size > 0)
        {
#ifdef LSB_FIRST
          /* Byteswap ROM to optimize 16-bit access */
          int i;
          for (i = 0; i < size; i += 2)
          {
            uint8 temp = scd.bootrom[i];
            scd.bootrom[i] = scd.bootrom[i+1];
            scd.bootrom[i+1] = temp;
          }
#endif
          /* mark CD BIOS as being loaded */
          system_bios = system_bios | 0x10;

          /* loaded BIOS region */
          system_bios = (system_bios & 0xf0) | (region_code >> 4);
        }

        return size;
      }
      
      return -1;
    }

    case SYSTEM_GG:
    case SYSTEM_GGMS:
    {
      /* check if Game Gear BOOTROM is already loaded */
      if (!(system_bios & SYSTEM_GG))
      {      
        /* mark both Master System & Game Gear BOOTROM as unloaded */
        system_bios &= ~(SYSTEM_SMS | SYSTEM_GG);

        /* BOOTROM is stored above cartridge ROM area (max. 4MB) */
        if (cart.romsize <= 0x400000)
        {
          /* load Game Gear BOOTROM file */
          size = load_archive(GG_BIOS, cart.rom + 0x400000, 0x100000, 0);

          if (size > 0)
          {
            /* mark Game Gear BOOTROM as loaded */
            system_bios |= SYSTEM_GG;
          }
        }

        return size;
      }
      
      return -1;
    }

    case SYSTEM_SMS:
    case SYSTEM_SMS2:
    {
      /* check if Master System BOOTROM is already loaded */
      if (!(system_bios & SYSTEM_SMS) || ((system_bios & 0x0c) != (region_code >> 4)))
      {      
        /* mark both Master System & Game Gear BOOTROM as unloaded */
        system_bios &= ~(SYSTEM_SMS | SYSTEM_GG);

        /* BOOTROM is stored above cartridge ROM area (max. 4MB) */
        if (cart.romsize <= 0x400000)
        {
          /* load Master System BOOTROM file */
          switch (region_code)
          {
            case REGION_USA:
              size = load_archive(MS_BIOS_US, cart.rom + 0x400000, 0x400000, 0);
              break;
            case REGION_EUROPE:
              size = load_archive(MS_BIOS_EU, cart.rom + 0x400000, 0x400000, 0);
              break;
            default:
              size = load_archive(MS_BIOS_JP, cart.rom + 0x400000, 0x400000, 0);
              break;
          }

          if (size > 0)
          {
            /* mark Master System BOOTROM as loaded */
            system_bios |= SYSTEM_SMS;

            /* loaded BOOTROM region */
            system_bios = (system_bios & 0xf0) | (region_code >> 4);
          }
        }

        return size;
      }
      
      return -1;
    }

    default:
    {
      return 0;
    }
  }
}