#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int s32 ;
struct TYPE_6__ {int width; int height; int /*<<< orphan*/  data; int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ gx_texture ;
struct TYPE_5__ {int w; int x; int h; int y; } ;
struct TYPE_7__ {TYPE_1__ viewport; } ;
typedef  int /*<<< orphan*/  GXTexObj ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 scalar_t__ BLACK ; 
 int /*<<< orphan*/  DCFlushRange (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_Begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_CLAMP ; 
 int /*<<< orphan*/  GX_Color4u8 (int,int,int,int) ; 
 int /*<<< orphan*/  GX_CopyTex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_DrawDone () ; 
 int /*<<< orphan*/  GX_End () ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  GX_InitTexObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_InvalidateTexAll () ; 
 int /*<<< orphan*/  GX_LoadTexObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_PixModeSync () ; 
 int /*<<< orphan*/  GX_Position2s16 (int,int) ; 
 int /*<<< orphan*/  GX_QUADS ; 
 int /*<<< orphan*/  GX_SetTexCopyDst (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTexCopySrc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GX_TEXMAP0 ; 
 int /*<<< orphan*/  GX_TF_RGB565 ; 
 int /*<<< orphan*/  GX_TF_RGBA8 ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  GX_TexCoord2f32 (double,double) ; 
 int /*<<< orphan*/  GX_VTXFMT0 ; 
 TYPE_4__ bitmap ; 
 int /*<<< orphan*/  gxDrawRectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screenshot ; 
 int /*<<< orphan*/  texturemem ; 
 int /*<<< orphan*/  vheight ; 
 int /*<<< orphan*/  vwidth ; 

void gxCopyScreenshot(gx_texture *texture)
{
  /* retrieve gamescreen texture */
  GXTexObj texobj;
  GX_InitTexObj(&texobj, texturemem, vwidth, vheight, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
  GX_LoadTexObj(&texobj, GX_TEXMAP0);
  GX_InvalidateTexAll();

  /* scale texture to EFB width */
  s32 w = ((bitmap.viewport.w + 2*bitmap.viewport.x) * 640) / bitmap.viewport.w;
  s32 h = (bitmap.viewport.h + 2*bitmap.viewport.y) * 2;
  s32 x = -w/2;
  s32 y = -(240+ 2*bitmap.viewport.y);

  /* black out surrounding area if necessary (Game Gear without borders) */
  if ((w < 640) || (h < 480))
  {
    gxDrawRectangle(0, 0, 640, 480, 255, (GXColor)BLACK);
  }

  /* draw textured quad */
  GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
  GX_Position2s16(x,y+h);
  GX_Color4u8(0xff,0xff,0xff,0xff);
  GX_TexCoord2f32(0.0, 1.0);
  GX_Position2s16(x+w,y+h);
  GX_Color4u8(0xff,0xff,0xff,0xff);
  GX_TexCoord2f32(1.0, 1.0);
  GX_Position2s16(x+w,y);
  GX_Color4u8(0xff,0xff,0xff,0xff);
  GX_TexCoord2f32(1.0, 0.0);
  GX_Position2s16(x,y);
  GX_Color4u8(0xff,0xff,0xff,0xff);
  GX_TexCoord2f32(0.0, 0.0);
  GX_End();

  /* copy EFB to texture */
  texture->format = GX_TF_RGBA8;
  texture->width = 320;
  texture->height = bitmap.viewport.h;
  texture->data = screenshot;
  GX_SetTexCopySrc(0, 0, texture->width * 2, texture->height * 2);
  GX_SetTexCopyDst(texture->width, texture->height, texture->format, GX_TRUE);
  GX_DrawDone();
  GX_CopyTex(texture->data, GX_TRUE);
  GX_Flush();

  /* wait for copy operation to finish */
  /* GX_PixModeSync is only useful if GX_ command follows */
  /* we use dummy GX commands to stall CPU execution */
  GX_PixModeSync();
  GX_LoadTexObj(&texobj, GX_TEXMAP0);
  GX_InvalidateTexAll();
  GX_Flush();
  DCFlushRange(texture->data, texture->width * texture->height * 4);
}