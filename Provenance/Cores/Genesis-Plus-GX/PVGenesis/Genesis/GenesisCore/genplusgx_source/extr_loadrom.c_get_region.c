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
struct TYPE_4__ {int region_detect; int vdp_mode; int master_clock; } ;
struct TYPE_3__ {int checksum; int realchecksum; int /*<<< orphan*/  product; scalar_t__* country; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLOCK_NTSC ; 
 int /*<<< orphan*/  MCLOCK_PAL ; 
 int REGION_EUROPE ; 
 int REGION_JAPAN_NTSC ; 
 int REGION_JAPAN_PAL ; 
 int REGION_USA ; 
 int SYSTEM_MCD ; 
 int SYSTEM_MD ; 
 TYPE_2__ config ; 
 int /*<<< orphan*/  memcmp (scalar_t__*,char*,int) ; 
 int region_code ; 
 int rom_region ; 
 TYPE_1__ rominfo ; 
 int sms_cart_region_detect () ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  system_clock ; 
 int system_hw ; 
 char toupper (int) ; 
 int vdp_pal ; 

void get_region(char *romheader)
{
  /* region auto-detection ? */
  if (romheader)
  {
    /* Mega CD image */
    if (system_hw == SYSTEM_MCD)
    {
      /* security code */
      switch (romheader[0x20b])
      {
        case 0x7a:
          region_code = REGION_USA;
          break;

        case 0x64:
          region_code = REGION_EUROPE;
          break;
   
        default:
          region_code = REGION_JAPAN_NTSC;
          break;
      }
    }

    /* 16-bit cartridge */
    else if (system_hw & SYSTEM_MD)
    {
      /* country codes used to differentiate region */
      /* 0001 = japan ntsc (1) */
      /* 0010 = japan pal  (2) -> does not exist ? */
      /* 0100 = usa        (4) */
      /* 1000 = europe     (8) */
      int country = 0;

      /* from Gens */
      if (!memcmp(rominfo.country, "eur", 3)) country |= 8;
      else if (!memcmp(rominfo.country, "EUR", 3)) country |= 8;
      else if (!memcmp(rominfo.country, "jap", 3)) country |= 1;
      else if (!memcmp(rominfo.country, "JAP", 3)) country |= 1;
      else if (!memcmp(rominfo.country, "usa", 3)) country |= 4;
      else if (!memcmp(rominfo.country, "USA", 3)) country |= 4;
      else
      {
        int i;
        char c;

        /* look for each characters */
        for(i = 0; i < 4; i++)
        {
          c = toupper((int)rominfo.country[i]);

          if (c == 'U') country |= 4;
          else if (c == 'J') country |= 1;
          else if (c == 'E') country |= 8;
          else if (c == 'K') country |= 1;
          else if (c < 16) country |= c;
          else if ((c >= '0') && (c <= '9')) country |= c - '0';
          else if ((c >= 'A') && (c <= 'F')) country |= c - 'A' + 10;
        }
      }

      /* set default console region (USA > JAPAN > EUROPE) */
      if (country & 4) region_code = REGION_USA;
      else if (country & 1) region_code = REGION_JAPAN_NTSC;
      else if (country & 8) region_code = REGION_EUROPE;
      else if (country & 2) region_code = REGION_JAPAN_PAL;
      else region_code = REGION_USA;

      /* some games need specific region settings but have wrong header*/
      if (((strstr(rominfo.product,"T-45033") != NULL) && (rominfo.checksum == 0x0F81)) || /* Alisia Dragon (Europe) */
           (strstr(rominfo.product,"T-69046-50") != NULL) ||    /* Back to the Future III (Europe) */
           (strstr(rominfo.product,"T-120106-00") != NULL) ||   /* Brian Lara Cricket (Europe) */
           (strstr(rominfo.product,"T-70096 -00") != NULL))     /* Muhammad Ali Heavyweight Boxing (Europe) */
      {
        /* need PAL settings */
        region_code = REGION_EUROPE;
      }
      else if ((rominfo.realchecksum == 0x532e) && (strstr(rominfo.product,"1011-00") != NULL)) 
      {
        /* On Dal Jang Goon (Korea) needs JAPAN region code */
        region_code = REGION_JAPAN_NTSC;
      }
    }

    /* 8-bit cartridge */
    else
    {
      region_code = sms_cart_region_detect();
    }

    /* save auto-detected region */
    rom_region = region_code;
  }
  else
  {
    /* restore auto-detected region */
    region_code = rom_region;
  }
  
  /* force console region if requested */
  if (config.region_detect == 1) region_code = REGION_USA;
  else if (config.region_detect == 2) region_code = REGION_EUROPE;
  else if (config.region_detect == 3) region_code = REGION_JAPAN_NTSC;
  else if (config.region_detect == 4) region_code = REGION_JAPAN_PAL;

  /* autodetect PAL/NTSC timings */
  vdp_pal = (region_code >> 6) & 0x01;

  /* autodetect PAL/NTSC master clock */
  system_clock = vdp_pal ? MCLOCK_PAL : MCLOCK_NTSC;

  /* force PAL/NTSC timings if requested */
  if (config.vdp_mode == 1) vdp_pal = 0;
  else if (config.vdp_mode == 2) vdp_pal = 1;

  /* force PAL/NTSC master clock if requested */
  if (config.master_clock == 1) system_clock = MCLOCK_NTSC;
  else if (config.master_clock == 2) system_clock = MCLOCK_PAL;
}