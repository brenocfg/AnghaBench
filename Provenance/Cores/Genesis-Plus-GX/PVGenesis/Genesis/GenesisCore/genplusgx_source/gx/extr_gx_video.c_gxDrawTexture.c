#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ data; } ;
typedef  TYPE_1__ gx_texture ;
struct TYPE_5__ {int fbWidth; int efbHeight; } ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 int /*<<< orphan*/  GX_ANISO_4 ; 
 int /*<<< orphan*/  GX_Begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_CLAMP ; 
 int /*<<< orphan*/  GX_Color4u8 (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_DrawDone () ; 
 int /*<<< orphan*/  GX_End () ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_InitTexObj (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_InitTexObjLOD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_InvalidateTexAll () ; 
 int /*<<< orphan*/  GX_LINEAR ; 
 int /*<<< orphan*/  GX_LIN_MIP_LIN ; 
 int /*<<< orphan*/  GX_LoadTexObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_Position2s16 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GX_QUADS ; 
 int /*<<< orphan*/  GX_TEXMAP0 ; 
 int /*<<< orphan*/  GX_TF_RGBA8 ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  GX_TexCoord2f32 (double,double) ; 
 int /*<<< orphan*/  GX_VTXFMT0 ; 
 TYPE_2__* vmode ; 

void gxDrawTexture(gx_texture *texture, s32 x, s32 y, s32 w, s32 h, u8 alpha)
{
  if (!texture) return;
  if (texture->data)
  {
    /* load texture object */
    GXTexObj texObj;
    GX_InitTexObj(&texObj, texture->data, texture->width, texture->height, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GX_InitTexObjLOD(&texObj,GX_LINEAR,GX_LIN_MIP_LIN,0.0,10.0,0.0,GX_FALSE,GX_TRUE,GX_ANISO_4); /* does this really change anything ? */
    GX_LoadTexObj(&texObj, GX_TEXMAP0);
    GX_InvalidateTexAll();

    /* vertex coordinate */
    x -= (vmode->fbWidth/2);
    y -= (vmode->efbHeight/2);

    /* draw textured quad */
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
    GX_Position2s16(x,y+h);
    GX_Color4u8(0xff,0xff,0xff,alpha);
    GX_TexCoord2f32(0.0, 1.0);
    GX_Position2s16(x+w,y+h);
    GX_Color4u8(0xff,0xff,0xff,alpha);
    GX_TexCoord2f32(1.0, 1.0);
    GX_Position2s16(x+w,y);
    GX_Color4u8(0xff,0xff,0xff,alpha);
    GX_TexCoord2f32(1.0, 0.0);
    GX_Position2s16(x,y);
    GX_Color4u8(0xff,0xff,0xff,alpha);
    GX_TexCoord2f32(0.0, 0.0);
    GX_End();
    GX_DrawDone();
  }
}