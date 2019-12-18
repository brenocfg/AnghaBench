#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_19__ {int /*<<< orphan*/  vfilter; scalar_t__ render; int /*<<< orphan*/  bilinear; scalar_t__ ntsc; scalar_t__ vsync; } ;
struct TYPE_18__ {scalar_t__* system; int /*<<< orphan*/ ** analog; } ;
struct TYPE_17__ {TYPE_2__* regs; } ;
struct TYPE_16__ {int viTVMode; } ;
struct TYPE_15__ {int changed; int w; int x; int h; int y; } ;
struct TYPE_13__ {int h; } ;
struct TYPE_14__ {TYPE_1__ byte; } ;
struct TYPE_12__ {TYPE_3__ viewport; } ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 int /*<<< orphan*/  DCFlushRange (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_ANISO_1 ; 
 int /*<<< orphan*/  GX_CLAMP ; 
 int /*<<< orphan*/  GX_CopyDisp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_DrawDone () ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  GX_InitTexObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_InitTexObjLOD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_InvalidateTexAll () ; 
 int /*<<< orphan*/  GX_LoadTexObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_NEAR ; 
 int /*<<< orphan*/  GX_NEAR_MIP_NEAR ; 
 int /*<<< orphan*/  GX_TEXMAP0 ; 
 int /*<<< orphan*/  GX_TF_RGB565 ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int MD_NTSC_OUT_WIDTH (int) ; 
 int NO_SYNC ; 
 int SMS_NTSC_OUT_WIDTH (int) ; 
 int SYNC_VIDEO ; 
 scalar_t__ SYSTEM_LIGHTPHASER ; 
 int /*<<< orphan*/  TEX_SIZE ; 
 int /*<<< orphan*/  VIDEO_Configure (TYPE_4__*) ; 
 int /*<<< orphan*/  VIDEO_Flush () ; 
 scalar_t__ VIDEO_GetNextField () ; 
 int /*<<< orphan*/  VIDEO_SetNextFramebuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_WaitVSync () ; 
 int VI_NON_INTERLACE ; 
 scalar_t__ audioStarted ; 
 TYPE_10__ bitmap ; 
 scalar_t__** cd_leds ; 
 TYPE_9__ config ; 
 scalar_t__* crosshair ; 
 int /*<<< orphan*/  draw_square () ; 
 int gc_pal ; 
 int /*<<< orphan*/  gxDrawCdLeds (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gxDrawCrosshair (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxResetMode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxResetScaler (int) ; 
 TYPE_7__ input ; 
 int interlaced ; 
 scalar_t__ odd_frame ; 
 int* reg ; 
 TYPE_4__* rmode ; 
 TYPE_5__ scd ; 
 int /*<<< orphan*/  texturemem ; 
 TYPE_4__** tvmodes ; 
 int vdp_pal ; 
 int vheight ; 
 int video_sync ; 
 int vwidth ; 
 int whichfb ; 
 int /*<<< orphan*/ * xfb ; 

int gx_video_Update(void)
{
  if (video_sync) return NO_SYNC;

  video_sync = config.vsync && (gc_pal == vdp_pal);

  /* check if display has changed during frame */
  if (bitmap.viewport.changed & 1)
  {
    /* update texture size */
    vwidth = bitmap.viewport.w + (2 * bitmap.viewport.x);
    vheight = bitmap.viewport.h + (2 * bitmap.viewport.y);

    /* interlaced mode */
    if (config.render && interlaced)
    {
      vheight = vheight << 1;
    }

    /* ntsc filter */
    if (config.ntsc)
    {
      vwidth = (reg[12] & 1) ? MD_NTSC_OUT_WIDTH(vwidth) : SMS_NTSC_OUT_WIDTH(vwidth);

      /* texel width must remain multiple of 4 */
      vwidth  = (vwidth >> 2) << 2;
    }

    /* initialize texture object */
    GXTexObj texobj;
    GX_InitTexObj(&texobj, texturemem, vwidth, vheight, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);

    /* configure texture filtering */
    if (!config.bilinear)
    {
      GX_InitTexObjLOD(&texobj,GX_NEAR,GX_NEAR_MIP_NEAR,0.0,10.0,0.0,GX_FALSE,GX_FALSE,GX_ANISO_1);
    }

    /* load texture object */
    GX_LoadTexObj(&texobj, GX_TEXMAP0);

    /* update rendering mode */
    if (config.render)
    {
      rmode = tvmodes[gc_pal*3 + 2];
    }
    else
    {
      rmode = tvmodes[gc_pal*3 + interlaced];
    }

    /* update aspect ratio */
    gxResetScaler(vwidth);

    /* update GX rendering mode */
    gxResetMode(rmode, config.vfilter);

    /* update VI mode */
    VIDEO_Configure(rmode);
  }

  /* texture is now directly mapped by the line renderer */

  /* force texture cache update */
  DCFlushRange(texturemem, TEX_SIZE);
  GX_InvalidateTexAll();

  /* render textured quad */
  draw_square();

  /* lightgun # 1 screen mark */
  if (crosshair[0])
  {
    if (input.system[0] == SYSTEM_LIGHTPHASER)
    {
      gxDrawCrosshair(crosshair[0], input.analog[0][0],input.analog[0][1]);
    }
    else
    {
      gxDrawCrosshair(crosshair[0], input.analog[4][0],input.analog[4][1]);
    }
  }

  /* lightgun #2 screen mark */
  if (crosshair[1])
  {
    if (input.system[1] == SYSTEM_LIGHTPHASER)
    {
      gxDrawCrosshair(crosshair[1], input.analog[4][0],input.analog[4][1]);
    }
    else
    {
      gxDrawCrosshair(crosshair[1], input.analog[5][0],input.analog[5][1]);
    }
  }

  /* CD LEDS */
  if (cd_leds[1][1])
  {
    /* CD LEDS status */
    u8 mode = scd.regs[0x06 >> 1].byte.h;
    gxDrawCdLeds(cd_leds[1][(mode >> 1) & 1], cd_leds[0][mode & 1]);
  }

  /* swap XFB */ 
  whichfb ^= 1;

  /* copy EFB to XFB */
  GX_DrawDone();
  GX_CopyDisp(xfb[whichfb], GX_TRUE);
  GX_Flush();

  /* XFB is ready to be displayed */
  VIDEO_SetNextFramebuffer(xfb[whichfb]);
  VIDEO_Flush();

  if (bitmap.viewport.changed & 1)
  {
    /* clear update flags */
    bitmap.viewport.changed &= ~1;

    /* field synchronization */
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE)
    {
      VIDEO_WaitVSync();
    }
    else while (VIDEO_GetNextField() != odd_frame)
    {
      VIDEO_WaitVSync();
    }

    /* Audio DMA need to be resynchronized with VSYNC */                    
    audioStarted = 0;
  }

  return SYNC_VIDEO;
}