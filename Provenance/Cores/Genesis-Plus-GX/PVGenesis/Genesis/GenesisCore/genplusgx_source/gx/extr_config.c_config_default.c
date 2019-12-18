#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {int psg_preamp; int fm_preamp; int hq_fm; int psgBoostNoise; int filter; int lp_range; int low_freq; int high_freq; double lg; double mg; double hg; int dac_bits; int ym2413; int addr_error; int aspect; int overscan; int vsync; int bilinear; int vfilter; int render; int tv_mode; double gamma; int* gun_cursor; int s_auto; int v_prog; int s_default; int screen_w; double bgm_volume; double sfx_volume; TYPE_1__* input; int /*<<< orphan*/ ** lastdir; scalar_t__ bg_overlay; scalar_t__ l_device; scalar_t__ s_device; scalar_t__ autocheat; scalar_t__ autoload; scalar_t__ cd_leds; scalar_t__ invert_mouse; scalar_t__ trap; scalar_t__ ntsc; scalar_t__ gg_extra; scalar_t__ yscale; scalar_t__ xscale; scalar_t__ yshift; scalar_t__ xshift; scalar_t__ hot_swap; scalar_t__ lock_on; scalar_t__ bios; scalar_t__ force_dtack; scalar_t__ master_clock; scalar_t__ vdp_mode; scalar_t__ region_detect; scalar_t__ system; scalar_t__ mono; int /*<<< orphan*/  version; } ;
struct TYPE_9__ {void** system; } ;
struct TYPE_8__ {int viTVMode; } ;
struct TYPE_7__ {int device; } ;

/* Variables and functions */
 int ASND_GetFirstUnusedVoice () ; 
 int /*<<< orphan*/  ASND_Pause (int) ; 
 int /*<<< orphan*/  ASND_SetVoice (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONFIG_VERSION ; 
 char* DEFAULT_PATH ; 
 int /*<<< orphan*/  GUI_WaitPrompt (char*,char*) ; 
 void* NO_SYSTEM ; 
 int PAD_BUTTON_B ; 
 int PAD_ButtonsHeld (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAD_ScanPads () ; 
 void* SYSTEM_MD_GAMEPAD ; 
 TYPE_2__ TVNtsc480Prog ; 
 size_t TYPE_DVD ; 
 size_t TYPE_SD ; 
 size_t TYPE_USB ; 
 int /*<<< orphan*/  VIDEO_Configure (TYPE_2__*) ; 
 int /*<<< orphan*/  VIDEO_Flush () ; 
 scalar_t__ VIDEO_HaveComponentCable () ; 
 int /*<<< orphan*/  VIDEO_WaitVSync () ; 
#define  VI_EURGB60 129 
 double VI_GM_1_0 ; 
#define  VI_PAL 128 
 int /*<<< orphan*/  VOICE_MONO_16BIT ; 
 TYPE_4__ config ; 
 int config_load () ; 
 int /*<<< orphan*/  gx_input_SetDefault () ; 
 TYPE_3__ input ; 
 int /*<<< orphan*/  input_init () ; 
 scalar_t__ intro_pcm ; 
 int /*<<< orphan*/  intro_pcm_size ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* vmode ; 

void config_default(void)
{
  /* version TAG */
  strncpy(config.version,CONFIG_VERSION,16);

  /* sound options */
  config.psg_preamp     = 150;
  config.fm_preamp      = 100;
  config.hq_fm          = 1;
  config.psgBoostNoise  = 1;
  config.filter         = 1;
  config.lp_range       = 0x9999; /* 0.6 in 16.16 fixed point */
  config.low_freq       = 880;
  config.high_freq      = 5000;
  config.lg             = 1.0;
  config.mg             = 1.0;
  config.hg             = 1.0;
  config.dac_bits       = 14;
  config.ym2413         = 2; /* AUTO */
  config.mono           = 0;

  /* system options */
  config.system         = 0; /* AUTO */
  config.region_detect  = 0; /* AUTO */
  config.vdp_mode       = 0; /* AUTO */
  config.master_clock   = 0; /* AUTO */
  config.force_dtack    = 0;
  config.addr_error     = 1;
  config.bios           = 0;
  config.lock_on        = 0;
  config.hot_swap       = 0;

  /* video options */
  config.xshift   = 0;
  config.yshift   = 0;
  config.xscale   = 0;
  config.yscale   = 0;
  config.aspect   = 1;
  config.overscan = 3; /* FULL */
  config.gg_extra = 0;
  config.ntsc     = 0;
  config.vsync    = 1; /* AUTO */
  config.bilinear = 1;
  config.vfilter  = 1;

  if (VIDEO_HaveComponentCable())
  {
    config.render = 2;
  }
  else
  {
    config.render = 0;
  }

  switch (vmode->viTVMode >> 2)
  {
    case VI_PAL:
      config.tv_mode = 1; /* 50hz only */
      break;

    case VI_EURGB60:
      config.tv_mode = 2; /* 50/60hz */
      break;
    
    default:
      config.tv_mode = 0; /* 60hz only */
      break;
  }

#ifdef HW_RVL
  config.trap = 0;
  config.gamma = VI_GM_1_0 / 10.0;
#endif

  /* controllers options */
  config.gun_cursor[0]  = 1;
  config.gun_cursor[1]  = 1;
  config.invert_mouse   = 0;

  /* on-screen options */
  config.cd_leds = 0;

  /* menu options */
  config.autoload     = 0;
  config.autocheat    = 0;
#ifdef HW_RVL
  config.s_auto       = 1;
#else
  config.s_auto       = 0;
  config.v_prog       = 1;
#endif
  config.s_default    = 1;
  config.s_device     = 0;
  config.l_device     = 0;
  config.bg_overlay   = 0;
  config.screen_w     = 658;
  config.bgm_volume   = 100.0;
  config.sfx_volume   = 100.0;

  /* default ROM directories */
#ifdef HW_RVL
  sprintf (config.lastdir[0][TYPE_SD],  "sd:%s/roms/",  DEFAULT_PATH);
  sprintf (config.lastdir[1][TYPE_SD],  "sd:%s/roms/",  DEFAULT_PATH);
  sprintf (config.lastdir[2][TYPE_SD],  "sd:%s/roms/",  DEFAULT_PATH);
  sprintf (config.lastdir[3][TYPE_SD],  "sd:%s/roms/",  DEFAULT_PATH);
  sprintf (config.lastdir[4][TYPE_SD],  "sd:%s/roms/",  DEFAULT_PATH);
  sprintf (config.lastdir[0][TYPE_USB], "usb:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[1][TYPE_USB], "usb:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[2][TYPE_USB], "usb:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[3][TYPE_USB], "usb:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[4][TYPE_USB], "usb:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[0][TYPE_DVD], "dvd:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[1][TYPE_DVD], "dvd:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[2][TYPE_DVD], "dvd:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[3][TYPE_DVD], "dvd:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[4][TYPE_DVD], "dvd:%s/roms/", DEFAULT_PATH);
#else
  sprintf (config.lastdir[0][TYPE_SD],  "%s/roms/",  DEFAULT_PATH);
  sprintf (config.lastdir[1][TYPE_SD],  "%s/roms/",  DEFAULT_PATH);
  sprintf (config.lastdir[2][TYPE_SD],  "%s/roms/",  DEFAULT_PATH);
  sprintf (config.lastdir[3][TYPE_SD],  "%s/roms/",  DEFAULT_PATH);
  sprintf (config.lastdir[4][TYPE_SD],  "%s/roms/",  DEFAULT_PATH);
  sprintf (config.lastdir[0][TYPE_DVD], "dvd:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[1][TYPE_DVD], "dvd:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[2][TYPE_DVD], "dvd:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[3][TYPE_DVD], "dvd:%s/roms/", DEFAULT_PATH);
  sprintf (config.lastdir[4][TYPE_DVD], "dvd:%s/roms/", DEFAULT_PATH);
#endif

  /* try to restore user config */
  int loaded = config_load();

#ifndef HW_RVL
  /* detect progressive mode enable/disable requests */
  PAD_ScanPads();
  if (PAD_ButtonsHeld(0) & PAD_BUTTON_B)
  {
    /* swap progressive mode enable flag and play some sound to inform user */
    config.v_prog ^= 1;
    ASND_Pause(0);
    int voice = ASND_GetFirstUnusedVoice();
    ASND_SetVoice(voice,VOICE_MONO_16BIT,44100,0,(u8 *)intro_pcm,intro_pcm_size,200,200,NULL);
    sleep (2);
    ASND_Pause(1);
  }

  /* switch into 480p if component cable has been detected and progressive mode is enabled */
  if (VIDEO_HaveComponentCable() && config.v_prog)
  {
    vmode = &TVNtsc480Prog;
    VIDEO_Configure (vmode);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    VIDEO_WaitVSync();
  }
#endif

  /* inform user if default config is used */
  if (!loaded)
  {
    GUI_WaitPrompt("Warning","Default Settings restored");
    gx_input_SetDefault();
  }

  /* default emulated inputs */
  input.system[0] = SYSTEM_MD_GAMEPAD;
  input.system[1] = (config.input[1].device != -1) ? SYSTEM_MD_GAMEPAD : NO_SYSTEM;
  input_init();
}