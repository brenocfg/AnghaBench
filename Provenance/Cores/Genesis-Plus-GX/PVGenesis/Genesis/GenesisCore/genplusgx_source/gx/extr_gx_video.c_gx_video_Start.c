#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sms_ntsc_t ;
typedef  int /*<<< orphan*/  md_ntsc_t ;
struct TYPE_7__ {int x; int changed; } ;
struct TYPE_12__ {TYPE_1__ viewport; } ;
struct TYPE_11__ {double gamma; int tv_mode; int render; int overscan; int ntsc; scalar_t__ cd_leds; scalar_t__* gun_cursor; TYPE_2__* input; int /*<<< orphan*/  gg_extra; scalar_t__ vsync; int /*<<< orphan*/  trap; } ;
struct TYPE_10__ {scalar_t__* dev; scalar_t__* system; } ;
struct TYPE_9__ {int viTVMode; int /*<<< orphan*/  xfbMode; } ;
struct TYPE_8__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD_access_off_png ; 
 int /*<<< orphan*/  CD_access_on_png ; 
 int /*<<< orphan*/  CD_ready_off_png ; 
 int /*<<< orphan*/  CD_ready_on_png ; 
 int /*<<< orphan*/  Crosshair_p1_png ; 
 int /*<<< orphan*/  Crosshair_p2_png ; 
 scalar_t__ DEVICE_LIGHTGUN ; 
 int MAX_DEVICES ; 
 scalar_t__ NO_DEVICE ; 
 scalar_t__ SYSTEM_GG ; 
 scalar_t__ SYSTEM_LIGHTPHASER ; 
 scalar_t__ SYSTEM_MCD ; 
 int /*<<< orphan*/  VIDEO_Flush () ; 
 int /*<<< orphan*/  VIDEO_SetGamma (int) ; 
 int /*<<< orphan*/  VIDEO_SetPostRetraceCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_SetTrapFilter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_WaitVSync () ; 
 int VI_TVMODE_NTSC_PROG ; 
 int /*<<< orphan*/  VI_XFBMODE_DF ; 
 int /*<<< orphan*/  VI_XFBMODE_SF ; 
 TYPE_6__ bitmap ; 
 void*** cd_leds ; 
 TYPE_5__ config ; 
 void** crosshair ; 
 int gc_pal ; 
 int /*<<< orphan*/  gxResetRendering (int /*<<< orphan*/ ) ; 
 void* gxTextureOpenPNG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ input ; 
 int /*<<< orphan*/ * md_ntsc ; 
 int /*<<< orphan*/  md_ntsc_composite ; 
 int /*<<< orphan*/  md_ntsc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_ntsc_rgb ; 
 int /*<<< orphan*/  md_ntsc_svideo ; 
 scalar_t__ memalign (int,int) ; 
 int /*<<< orphan*/ * sms_ntsc ; 
 int /*<<< orphan*/  sms_ntsc_composite ; 
 int /*<<< orphan*/  sms_ntsc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sms_ntsc_rgb ; 
 int /*<<< orphan*/  sms_ntsc_svideo ; 
 scalar_t__ system_hw ; 
 TYPE_3__** tvmodes ; 
 int vdp_pal ; 
 int /*<<< orphan*/  vi_callback ; 
 scalar_t__ video_sync ; 

void gx_video_Start(void)
{
#ifdef HW_RVL
  VIDEO_SetTrapFilter(config.trap);
  VIDEO_SetGamma((int)(config.gamma * 10.0));
#endif

  /* TV mode */
  if ((config.tv_mode == 1) || ((config.tv_mode == 2) && vdp_pal))
  {
    /* 50 Hz */
    gc_pal = 1;
  }
  else
  {
    /* 60 Hz */
    gc_pal = 0;
  }

  /* When VSYNC is set to AUTO & console TV mode matches emulated video mode, emulation is synchronized with video hardware as well */
  if (config.vsync && (gc_pal == vdp_pal))
  {
    /* VSYNC callback */
    VIDEO_SetPostRetraceCallback(vi_callback);
    VIDEO_Flush();
  }

  /* set interlaced or progressive video mode */
  if (config.render == 2)
  {
    tvmodes[2]->viTVMode = VI_TVMODE_NTSC_PROG;
    tvmodes[2]->xfbMode = VI_XFBMODE_SF;
  }
  else if (config.render == 1)
  {
    tvmodes[2]->viTVMode = tvmodes[0]->viTVMode & ~3;
    tvmodes[2]->xfbMode = VI_XFBMODE_DF;
  }

  /* update horizontal border width */
  if ((system_hw == SYSTEM_GG) && !config.gg_extra)
  {
    bitmap.viewport.x = (config.overscan & 2) ? 14 : -48;
  }
  else
  {
    bitmap.viewport.x = (config.overscan & 2) * 7;
  }

  /* force viewport update */
  bitmap.viewport.changed = 3;

  /* NTSC filter */
  if (config.ntsc)
  {
    /* allocate filters */
    if (!sms_ntsc)
    {
      sms_ntsc = (sms_ntsc_t *)memalign(32,sizeof(sms_ntsc_t));
    }
    if (!md_ntsc)
    {
      md_ntsc = (md_ntsc_t *)memalign(32,sizeof(md_ntsc_t));
    }

    /* setup filters default configuration */
    switch (config.ntsc)
    {
      case 1:
        sms_ntsc_init(sms_ntsc, &sms_ntsc_composite);
        md_ntsc_init(md_ntsc, &md_ntsc_composite);
        break;
      case 2:
        sms_ntsc_init(sms_ntsc, &sms_ntsc_svideo);
        md_ntsc_init(md_ntsc, &md_ntsc_svideo);
        break;
      case 3:
        sms_ntsc_init(sms_ntsc, &sms_ntsc_rgb);
        md_ntsc_init(md_ntsc, &md_ntsc_rgb);
        break;
    }
  }

  /* lightgun textures */
  int i, player = 0;
  for (i=0; i<MAX_DEVICES; i++)
  {
    /* Check for emulated lightguns */
    if (input.dev[i] == DEVICE_LIGHTGUN)
    {
      /* Check if input device is affected to player */
      if (config.input[player].device >= 0)
      {
        if ((i == 0) || ((i == 4) && (input.system[1] != SYSTEM_LIGHTPHASER)))
        {
          /* Lightgun #1 */
          if (config.gun_cursor[0])
          {
            crosshair[0] = gxTextureOpenPNG(Crosshair_p1_png,0);
          }
        }
        else
        {
          /* Lightgun #2 */
          if (config.gun_cursor[1])
          {
            crosshair[1] = gxTextureOpenPNG(Crosshair_p2_png,0);
          }
        }
      }
    }

    /* Check for any emulated device */
    if (input.dev[i] != NO_DEVICE)
    {
      /* increment player index */
      player++;
    }
  }

  /* CD leds textures */
  if (system_hw == SYSTEM_MCD)
  {
    if (config.cd_leds)
    {
      cd_leds[0][0] = gxTextureOpenPNG(CD_access_off_png,0);
      cd_leds[0][1] = gxTextureOpenPNG(CD_access_on_png,0);
      cd_leds[1][0] = gxTextureOpenPNG(CD_ready_off_png,0);
      cd_leds[1][1] = gxTextureOpenPNG(CD_ready_on_png,0);
    }
  }

  /* GX emulation rendering */
  gxResetRendering(0);

  /* resynchronize emulation with VSYNC */
  video_sync = 0;
  VIDEO_WaitVSync();
}