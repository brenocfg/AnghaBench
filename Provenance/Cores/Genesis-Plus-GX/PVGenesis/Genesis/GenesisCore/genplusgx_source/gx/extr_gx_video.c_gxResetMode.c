#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  f32 ;
struct TYPE_3__ {int efbHeight; int xfbHeight; int fbWidth; scalar_t__ xfbMode; int viHeight; int /*<<< orphan*/  field_rendering; int /*<<< orphan*/  vfilter; int /*<<< orphan*/  sample_pattern; int /*<<< orphan*/  aa; } ;
typedef  int /*<<< orphan*/  Mtx44 ;
typedef  TYPE_1__ GXRModeObj ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 scalar_t__ BLACK ; 
 int /*<<< orphan*/  GX_DISABLE ; 
 int /*<<< orphan*/  GX_ENABLE ; 
 int GX_FALSE ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  GX_GetYScaleFactor (int,int) ; 
 int /*<<< orphan*/  GX_LoadProjectionMtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_ORTHOGRAPHIC ; 
 int /*<<< orphan*/  GX_SetCopyClear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_SetCopyFilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetDispCopyDst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetDispCopySrc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GX_SetDispCopyYScale (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetFieldMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetScissor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GX_SetViewport (float,float,int,int,float,float) ; 
 int /*<<< orphan*/  VIDEO_PadFramebufferWidth (int) ; 
 scalar_t__ VI_XFBMODE_SF ; 
 int /*<<< orphan*/  guOrtho (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 

__attribute__((used)) static void gxResetMode(GXRModeObj *tvmode, int vfilter_enabled)
{
  Mtx44 p;
  f32 yScale = GX_GetYScaleFactor(tvmode->efbHeight, tvmode->xfbHeight);
  u16 xfbHeight = GX_SetDispCopyYScale(yScale);
  u16 xfbWidth  = VIDEO_PadFramebufferWidth(tvmode->fbWidth);  

  GX_SetCopyClear((GXColor)BLACK,0x00ffffff);
  GX_SetViewport(0.0F, 0.0F, tvmode->fbWidth, tvmode->efbHeight, 0.0F, 1.0F);
  GX_SetScissor(0, 0, tvmode->fbWidth, tvmode->efbHeight);
  GX_SetDispCopySrc(0, 0, tvmode->fbWidth, tvmode->efbHeight);
  GX_SetDispCopyDst(xfbWidth, xfbHeight);
  GX_SetCopyFilter(tvmode->aa, tvmode->sample_pattern, (tvmode->xfbMode == VI_XFBMODE_SF) ? GX_FALSE : vfilter_enabled, tvmode->vfilter);
  GX_SetFieldMode(tvmode->field_rendering, ((tvmode->viHeight == 2 * tvmode->xfbHeight) ? GX_ENABLE : GX_DISABLE));
  guOrtho(p, tvmode->efbHeight/2, -(tvmode->efbHeight/2), -(tvmode->fbWidth/2), tvmode->fbWidth/2, 100, 1000);
  GX_LoadProjectionMtx(p, GX_ORTHOGRAPHIC);
  GX_Flush();
}