#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  GX_BL_INVSRCALPHA ; 
 int /*<<< orphan*/  GX_BL_SRCALPHA ; 
 int /*<<< orphan*/  GX_BM_BLEND ; 
 int /*<<< orphan*/  GX_BM_NONE ; 
 int /*<<< orphan*/  GX_CLR_RGBA ; 
 int /*<<< orphan*/  GX_COLOR0A0 ; 
 int /*<<< orphan*/  GX_COLORNULL ; 
 int /*<<< orphan*/  GX_ClearVtxDesc () ; 
 int /*<<< orphan*/  GX_DIRECT ; 
 int /*<<< orphan*/  GX_F32 ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  GX_INDEX8 ; 
 int /*<<< orphan*/  GX_LO_CLEAR ; 
 int /*<<< orphan*/  GX_MODULATE ; 
 int /*<<< orphan*/  GX_POS_XY ; 
 int /*<<< orphan*/  GX_POS_XYZ ; 
 int /*<<< orphan*/  GX_REPLACE ; 
 int /*<<< orphan*/  GX_RGBA8 ; 
 int /*<<< orphan*/  GX_S16 ; 
 int /*<<< orphan*/  GX_SetArray (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_SetBlendMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetNumChans (int) ; 
 int /*<<< orphan*/  GX_SetNumTexGens (int) ; 
 int /*<<< orphan*/  GX_SetTevOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTevOrder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetVtxAttrFmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetVtxDesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_TEVSTAGE0 ; 
 int /*<<< orphan*/  GX_TEXCOORD0 ; 
 int /*<<< orphan*/  GX_TEXMAP0 ; 
 int /*<<< orphan*/  GX_TEX_ST ; 
 int /*<<< orphan*/  GX_VA_CLR0 ; 
 int /*<<< orphan*/  GX_VA_POS ; 
 int /*<<< orphan*/  GX_VA_TEX0 ; 
 int /*<<< orphan*/  GX_VTXFMT0 ; 
 int /*<<< orphan*/  square ; 

__attribute__((used)) static void gxResetRendering(u8 type)
{
  GX_ClearVtxDesc();

  if (type)
  {
    /* uses direct positionning, alpha blending & color channel (menu rendering) */
    GX_SetBlendMode(GX_BM_BLEND,GX_BL_SRCALPHA,GX_BL_INVSRCALPHA,GX_LO_CLEAR);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GX_SetVtxDesc (GX_VA_CLR0, GX_DIRECT);
    /* 
       Color.out = Color.rasterized*Color.texture
       Alpha.out = Alpha.rasterized*Alpha.texture 
    */
    GX_SetTevOp (GX_TEVSTAGE0, GX_MODULATE);
    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GX_SetNumTexGens(1);
    GX_SetNumChans(1);
  }
  else
  {
    /* uses array positionning, no alpha blending, no color channel (video emulation) */
    GX_SetBlendMode(GX_BM_NONE,GX_BL_SRCALPHA,GX_BL_INVSRCALPHA,GX_LO_CLEAR);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GX_SetVtxDesc(GX_VA_POS, GX_INDEX8);
    GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GX_SetArray(GX_VA_POS, square, 3 * sizeof (s16));
    /* 
       Color.out = Color.texture
       Alpha.out = Alpha.texture 
    */
    GX_SetTevOp (GX_TEVSTAGE0, GX_REPLACE);
    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLORNULL);
    GX_SetNumTexGens(1);
    GX_SetNumChans(0);
  }

  GX_Flush();
}