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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int screen_w; } ;
struct TYPE_5__ {int viWidth; int viXOrigin; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 scalar_t__ BLACK ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  VIDEO_Configure (TYPE_1__*) ; 
 int /*<<< orphan*/  VIDEO_SetGamma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_SetPostRetraceCallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIDEO_SetTrapFilter (int) ; 
 int /*<<< orphan*/  VIDEO_WaitVSync () ; 
 int /*<<< orphan*/  VI_GM_1_0 ; 
 int VI_MAX_WIDTH_NTSC ; 
 int /*<<< orphan*/ ** cd_leds ; 
 TYPE_3__ config ; 
 int /*<<< orphan*/ * crosshair ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gxClearScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxDrawScreenshot (int) ; 
 int /*<<< orphan*/  gxResetMode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxResetRendering (int) ; 
 int /*<<< orphan*/  gxSetScreen () ; 
 int /*<<< orphan*/  gxTextureClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * md_ntsc ; 
 int /*<<< orphan*/ * sms_ntsc ; 
 TYPE_1__* vmode ; 

void gx_video_Stop(void)
{
  /* wait for next VBLANK */
  VIDEO_WaitVSync ();

  /* unallocate NTSC filters */
  if (sms_ntsc) free(sms_ntsc);
  if (md_ntsc) free(md_ntsc);
  sms_ntsc = NULL;
  md_ntsc = NULL;

  /* lightgun textures */
  gxTextureClose(&crosshair[0]);
  gxTextureClose(&crosshair[1]);

  /* CD leds textures */
  gxTextureClose(&cd_leds[0][0]);
  gxTextureClose(&cd_leds[0][1]);
  gxTextureClose(&cd_leds[1][0]);
  gxTextureClose(&cd_leds[1][1]);

  /* GX menu rendering */
  gxResetRendering(1);
  gxResetMode(vmode, GX_TRUE);

  /* render game snapshot */
  gxClearScreen((GXColor)BLACK);
  gxDrawScreenshot(0xff);

  /* default VI settings */
  VIDEO_SetPostRetraceCallback(NULL);
#ifdef HW_RVL
  VIDEO_SetTrapFilter(1);
  VIDEO_SetGamma(VI_GM_1_0);
#endif

  /* adjust TV width */
  vmode->viWidth    = config.screen_w;
  vmode->viXOrigin  = (VI_MAX_WIDTH_NTSC - vmode->viWidth)/2;
  VIDEO_Configure(vmode);

  /* wait for VSYNC */
  gxSetScreen();
}