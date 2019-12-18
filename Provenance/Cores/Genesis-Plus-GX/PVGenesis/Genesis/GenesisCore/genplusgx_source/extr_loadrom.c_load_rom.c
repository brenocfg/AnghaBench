#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8 ;
typedef  int uint32 ;
struct TYPE_16__ {int romsize; int* rom; } ;
struct TYPE_15__ {scalar_t__ ram; } ;
struct TYPE_14__ {scalar_t__ loaded; } ;
struct TYPE_13__ {int system; } ;
struct TYPE_12__ {int* system; int x_offset; int y_offset; } ;
struct TYPE_11__ {int /*<<< orphan*/  international; int /*<<< orphan*/  product; int /*<<< orphan*/  domestic; int /*<<< orphan*/  ROMType; int /*<<< orphan*/  consoletype; } ;
struct TYPE_9__ {int boot; } ;
struct TYPE_10__ {int* bootrom; TYPE_1__ cartridge; } ;

/* Variables and functions */
 int SYSTEM_GG ; 
 int SYSTEM_GGMS ; 
 int SYSTEM_JUSTIFIER ; 
 int SYSTEM_MCD ; 
 int SYSTEM_MD ; 
 void* SYSTEM_MD_GAMEPAD ; 
 void* SYSTEM_MENACER ; 
 int SYSTEM_PBC ; 
 int SYSTEM_PICO ; 
 int SYSTEM_SG ; 
 int SYSTEM_SMS ; 
 int SYSTEM_SMS2 ; 
 int /*<<< orphan*/  areplay_shutdown () ; 
 TYPE_8__ cart ; 
 TYPE_7__ cdc ; 
 TYPE_6__ cdd ; 
 int cdd_load (char*,char*) ; 
 int /*<<< orphan*/  cdd_unload () ; 
 TYPE_5__ config ; 
 int /*<<< orphan*/  deinterleave_block (int*) ; 
 int /*<<< orphan*/  get_region (char*) ; 
 int /*<<< orphan*/  getrominfo (char*) ; 
 int /*<<< orphan*/  ggenie_shutdown () ; 
 TYPE_4__ input ; 
 int load_archive (char*,int*,int,char*) ; 
 scalar_t__ load_bios () ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int* old_system ; 
 int region_code ; 
 TYPE_3__ rominfo ; 
 int romtype ; 
 TYPE_2__ scd ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 int system_bios ; 
 int system_hw ; 

int load_rom(char *filename)
{
  int i, size;

  /* clear any existing patches */
  ggenie_shutdown();
  areplay_shutdown();

  /* check previous loaded ROM size */
  if (cart.romsize > 0x800000)
  {
    /* assume no CD is currently loaded */
    cdd.loaded = 0;
  }

  /* auto-detect CD image files */
  size = cdd_load(filename, (char *)(cart.rom));
  if (size < 0)
  {
    /* error opening file */
    return 0;
  }

  if (size > 0)
  {
    /* CD image file loaded */
    system_hw = SYSTEM_MCD;
  }
  else
  {
    /* load file into ROM buffer */
    char extension[4];
    size = load_archive(filename, cart.rom, sizeof(cart.rom), extension);
    if (!size)
    {
      /* mark all BOOTROM as unloaded since they could have been overwritten */
      system_bios &= ~(0x10 | SYSTEM_SMS | SYSTEM_GG);
      return 0;
    }

    /* mark BOOTROM as unloaded if they have been overwritten by cartridge ROM */
    if (size > 0x800000)
    {
      /* CD BIOS ROM are loaded at the start of CD area */
      system_bios &= ~0x10;
    }
    else if (size > 0x400000)
    {
      /* Master System or Game Gear BIOS ROM are loaded within $400000-$4FFFFF area */
      system_bios &= ~(SYSTEM_SMS | SYSTEM_GG);
    }

    /* convert lower case to upper case */
    *(uint32 *)(extension) &= 0xdfdfdfdf;

    /* auto-detect system hardware from ROM file extension */
    if (!memcmp("SMS", &extension[0], 3))
    {
      /* Master System II hardware */
      system_hw = SYSTEM_SMS2;
    }
    else if (!memcmp("GG", &extension[1], 2))
    {
      /* Game Gear hardware (GG mode) */
      system_hw = SYSTEM_GG;
    }
    else if (!memcmp("SG", &extension[1], 2))
    {
      /* SG-1000 hardware */
      system_hw = SYSTEM_SG;
    }
    else
    {
      /* Mega Drive hardware (Genesis mode) */
      system_hw = SYSTEM_MD;

      /* decode .MDX format */
      if (!memcmp("MDX", &extension[0], 3))
      {
        for (i = 4; i < size - 1; i++)
        {
          cart.rom[i-4] = cart.rom[i] ^ 0x40;
        }
        size = size - 5;
      }

      /* auto-detect byte-swapped dumps */
      if (!memcmp((char *)(cart.rom + 0x100),"ESAGM GE ARDVI E", 16) ||
          !memcmp((char *)(cart.rom + 0x100),"ESAGG NESESI", 12))
      {
        for(i = 0; i < size; i += 2)
        {
          uint8 temp = cart.rom[i];
          cart.rom[i] = cart.rom[i+1];
          cart.rom[i+1] = temp;
        }
      }
    }

    /* auto-detect 512 byte extra header */
    if (memcmp((char *)(cart.rom + 0x100), "SEGA", 4) && ((size / 512) & 1) && !(size % 512))
    {
      /* remove header */
      size -= 512;
      memcpy (cart.rom, cart.rom + 512, size);

      /* assume interleaved Genesis ROM format (.smd) */
      if (system_hw == SYSTEM_MD)
      {
        for (i = 0; i < (size / 0x4000); i++)
        {
          deinterleave_block (cart.rom + (i * 0x4000));
        }
      }
    }
  }
    
  /* initialize ROM size */
  cart.romsize = size;

  /* get infos from ROM header */
  getrominfo((char *)(cart.rom));

  /* set console region */
  get_region((char *)(cart.rom));

  /* CD image file */
  if (system_hw == SYSTEM_MCD)
  {   
    /* load CD BOOT ROM */
    if (!load_bios())
    {
      /* unmount CD image */
      cdd_unload();

      /* error loading CD BOOT ROM */
      return (0);
    }

    /* boot from CD */
    scd.cartridge.boot = 0x00;
  }

#ifdef LSB_FIRST
  /* 16-bit ROM specific */
  else if (system_hw == SYSTEM_MD)
  {
    /* Byteswap ROM to optimize 16-bit access */
    for (i = 0; i < cart.romsize; i += 2)
    {
      uint8 temp = cart.rom[i];
      cart.rom[i] = cart.rom[i+1];
      cart.rom[i+1] = temp;
    }
  }
#endif

  /* Save auto-detected system hardware  */
  romtype = system_hw;

  /* PICO ROM */
  if (strstr(rominfo.consoletype, "SEGA PICO") != NULL)
  {
    /* PICO hardware */
    system_hw = SYSTEM_PICO;
  }

  /* CD BOOTROM */
  else if (strstr(rominfo.ROMType, "BR") != NULL)
  {
    /* enable CD hardware */
    system_hw = SYSTEM_MCD;

    /* boot from CD */
    scd.cartridge.boot = 0x00;

    /* copy ROM to BOOTROM area */
    memcpy(scd.bootrom, cart.rom, sizeof(scd.bootrom));

    /* mark CD BIOS as being loaded */
    system_bios = system_bios | 0x10;

    /* loaded CD BIOS region */
    system_bios = (system_bios & 0xf0) | (region_code >> 4);
  }

  /* ROM cartridges with CD support */
  else if ((strstr(rominfo.domestic,"FLUX") != NULL) ||
           (strstr(rominfo.domestic,"WONDER LIBRARY") != NULL) ||
           (strstr(rominfo.product,"T-5740") != NULL))
  {
    /* check if console hardware is set to AUTO */
    if (config.system == 0x00)
    {
      /* auto-enable CD hardware */
      system_hw = SYSTEM_MCD;

      /* try to load CD BOOTROM */
      if (load_bios())
      {
        /* boot from cartridge */
        scd.cartridge.boot = 0x40;

        /* automatically load associated .iso image */
        strncpy(&filename[strlen(filename) - 4], ".iso", 4);
        cdd_load(filename, (char *)cdc.ram);
      }
      else
      {
        /* if not found, disable CD hardware */
        system_hw = SYSTEM_MD;
      }
    }
  }

  /* Force system hardware if requested */
  if (config.system == SYSTEM_MD)
  {
    if (!(system_hw & SYSTEM_MD))
    {
      /* Mega Drive in MS compatibility mode  */
      system_hw = SYSTEM_PBC;
    }
  }
  else if (config.system == SYSTEM_GG)
  {
    if (system_hw != SYSTEM_GG)
    {
      /* Game Gear in MS compatibility mode  */
      system_hw = SYSTEM_GGMS;
    }
  }
  else if (config.system)
  {
    system_hw = config.system;
  }

  /* restore previous input settings */
  if (old_system[0] != -1)
  {
    input.system[0] = old_system[0];
  }
  if (old_system[1] != -1)
  {
    input.system[1] = old_system[1];
  }

  /* default gun settings */
  input.x_offset = (input.system[1] == SYSTEM_MENACER) ? 64 : 0;
  input.y_offset = 0;

  /* autodetect gun support */
  if (strstr(rominfo.international,"MENACER") != NULL)
  {
    /* save current setting */
    if (old_system[0] == -1)
    {
      old_system[0] = input.system[0];
    }
    if (old_system[1] == -1)
    {
      old_system[1] = input.system[1];
    }

    /* force MENACER configuration */
    input.system[0] = SYSTEM_MD_GAMEPAD;
    input.system[1] = SYSTEM_MENACER;
    input.x_offset = 82;
    input.y_offset = 0;
  }
  else if (strstr(rominfo.international,"T2 ; THE ARCADE GAME") != NULL)
  {
    /* save current setting */
    if (old_system[0] == -1)
    {
      old_system[0] = input.system[0];
    }
    if (old_system[1] == -1)
    {
      old_system[1] = input.system[1];
    }

    /* force MENACER configuration */
    input.system[0] = SYSTEM_MD_GAMEPAD;
    input.system[1] = SYSTEM_MENACER;
    input.x_offset = 133;
    input.y_offset = -8;
  }
  else if (strstr(rominfo.international,"BODY COUNT") != NULL)
  {
    /* save current setting */
    if (old_system[0] == -1)
    {
      old_system[0] = input.system[0];
    }
    if (old_system[1] == -1)
    {
      old_system[1] = input.system[1];
    }

    /* force MENACER configuration */
    input.system[0] = SYSTEM_MD_GAMEPAD;
    input.system[1] = SYSTEM_MENACER;
    input.x_offset = 68;
    input.y_offset = -24;
  }
  else if (strstr(rominfo.international,"CORPSE KILLER") != NULL)
  {
    /* save current setting */
    if (old_system[0] == -1)
    {
      old_system[0] = input.system[0];
    }
    if (old_system[1] == -1)
    {
      old_system[1] = input.system[1];
    }

    /* force MENACER configuration */
    input.system[0] = SYSTEM_MD_GAMEPAD;
    input.system[1] = SYSTEM_MENACER;
    input.x_offset = 64;
    input.y_offset = -8;
  }
  else if (strstr(rominfo.international,"CRIME PATROL") != NULL)
  {
    /* save current setting */
    if (old_system[0] == -1)
    {
      old_system[0] = input.system[0];
    }
    if (old_system[1] == -1)
    {
      old_system[1] = input.system[1];
    }

    /* force MENACER configuration */
    input.system[0] = SYSTEM_MD_GAMEPAD;
    input.system[1] = SYSTEM_MENACER;
    input.x_offset = 61;
    input.y_offset = 0;
  }
  else if (strstr(rominfo.international,"MAD DOG II THE LOST GOLD") != NULL)
  {
    /* save current setting */
    if (old_system[0] == -1)
    {
      old_system[0] = input.system[0];
    }
    if (old_system[1] == -1)
    {
      old_system[1] = input.system[1];
    }

    /* force MENACER configuration */
    input.system[0] = SYSTEM_MD_GAMEPAD;
    input.system[1] = SYSTEM_MENACER;
    input.x_offset = 70;
    input.y_offset = 18;
  }
  else if (strstr(rominfo.international,"MAD DOG MCCREE") != NULL)
  {
    /* save current setting */
    if (old_system[0] == -1)
    {
      old_system[0] = input.system[0];
    }
    if (old_system[1] == -1)
    {
      old_system[1] = input.system[1];
    }

    /* force MENACER configuration */
    input.system[0] = SYSTEM_MD_GAMEPAD;
    input.system[1] = SYSTEM_MENACER;
    input.x_offset = 49;
    input.y_offset = 0;
  }
  else if (strstr(rominfo.international,"WHO SHOT JOHNNY ROCK?") != NULL)
  {
    /* save current setting */
    if (old_system[0] == -1)
    {
      old_system[0] = input.system[0];
    }
    if (old_system[1] == -1)
    {
      old_system[1] = input.system[1];
    }

    /* force MENACER configuration */
    input.system[0] = SYSTEM_MD_GAMEPAD;
    input.system[1] = SYSTEM_MENACER;
    input.x_offset = 60;
    input.y_offset = 30;
  }
  else if ((strstr(rominfo.international,"LETHAL ENFORCERS") != NULL) ||
           (strstr(rominfo.international,"SNATCHER") != NULL))
  {
    /* save current setting */
    if (old_system[0] == -1)
    {
      old_system[0] = input.system[0];
    }
    if (old_system[1] == -1)
    {
      old_system[1] = input.system[1];
    }

    /* force JUSTIFIER configuration */
    input.system[0] = SYSTEM_MD_GAMEPAD;
    input.system[1] = SYSTEM_JUSTIFIER;
    input.x_offset = (strstr(rominfo.international,"GUN FIGHTERS") != NULL) ? 24 : 0;
    input.y_offset = 0;
  }

  return(1);
}