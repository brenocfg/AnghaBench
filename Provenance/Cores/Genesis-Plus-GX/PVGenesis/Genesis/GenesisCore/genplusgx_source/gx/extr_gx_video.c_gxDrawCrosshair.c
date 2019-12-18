#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int width; int height; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ gx_texture ;
struct TYPE_7__ {int x; int y; } ;
struct TYPE_11__ {TYPE_1__ viewport; } ;
struct TYPE_10__ {int aspect; int /*<<< orphan*/  bilinear; } ;
struct TYPE_9__ {int fbWidth; int viWidth; int efbHeight; int viHeight; } ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 int /*<<< orphan*/  GX_ANISO_1 ; 
 int /*<<< orphan*/  GX_ANISO_4 ; 
 int /*<<< orphan*/  GX_Begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_CLAMP ; 
 int /*<<< orphan*/  GX_Color4u8 (int,int,int,int) ; 
 int /*<<< orphan*/  GX_End () ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_InitTexObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_InitTexObjLOD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_InvalidateTexAll () ; 
 int /*<<< orphan*/  GX_LINEAR ; 
 int /*<<< orphan*/  GX_LIN_MIP_LIN ; 
 int /*<<< orphan*/  GX_LoadTexObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_NEAR ; 
 int /*<<< orphan*/  GX_NEAR_MIP_NEAR ; 
 int /*<<< orphan*/  GX_Position2s16 (int,int) ; 
 int /*<<< orphan*/  GX_QUADS ; 
 int /*<<< orphan*/  GX_TEXMAP0 ; 
 int /*<<< orphan*/  GX_TF_RGB565 ; 
 int /*<<< orphan*/  GX_TF_RGBA8 ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  GX_TexCoord2f32 (double,double) ; 
 int /*<<< orphan*/  GX_VTXFMT0 ; 
 TYPE_6__ bitmap ; 
 TYPE_5__ config ; 
 int /*<<< orphan*/  gxResetRendering (int) ; 
 TYPE_3__* rmode ; 
 int* square ; 
 int /*<<< orphan*/  texturemem ; 
 int vheight ; 
 int vwidth ; 

__attribute__((used)) static void gxDrawCrosshair(gx_texture *texture, int x, int y)
{
  /* adjust texture dimensions to XFB->VI scaling */
  int w = (texture->width * rmode->fbWidth) / (rmode->viWidth);
  int h = (texture->height * rmode->efbHeight) / (rmode->viHeight);

  /* Aspect correction for widescreen TV */
  if (config.aspect & 2) w = (w * 3) / 4;

  /* EFB scale & shift */
  int xwidth = square[3] - square[9];
  int ywidth = square[4] - square[10];

  /* adjust texture coordinates to EFB */
  x = (((x + bitmap.viewport.x) * xwidth) / vwidth) + square[9] - w/2;
  y = (((y + bitmap.viewport.y) * ywidth) / vheight) + square[10] - h/2;

  /* reset GX rendering */
  gxResetRendering(1);

  /* load texture object */
  GXTexObj texObj;
  GX_InitTexObj(&texObj, texture->data, texture->width, texture->height, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
  GX_InitTexObjLOD(&texObj,GX_LINEAR,GX_LIN_MIP_LIN,0.0,10.0,0.0,GX_FALSE,GX_TRUE,GX_ANISO_4);
  GX_LoadTexObj(&texObj, GX_TEXMAP0);
  GX_InvalidateTexAll();

  /* Draw textured quad */
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

  /* restore GX rendering */
  gxResetRendering(0);

  /* restore texture object */
  GXTexObj texobj;
  GX_InitTexObj(&texobj, texturemem, vwidth, vheight, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
  if (!config.bilinear)
  {
    GX_InitTexObjLOD(&texobj,GX_NEAR,GX_NEAR_MIP_NEAR,0.0,10.0,0.0,GX_FALSE,GX_FALSE,GX_ANISO_1);
  }
  GX_LoadTexObj(&texobj, GX_TEXMAP0);
  GX_InvalidateTexAll();
}