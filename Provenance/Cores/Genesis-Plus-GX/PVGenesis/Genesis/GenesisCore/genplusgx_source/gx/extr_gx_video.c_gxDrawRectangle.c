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
struct TYPE_5__ {int fbWidth; int efbHeight; } ;
struct TYPE_4__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ GXColor ;

/* Variables and functions */
 int /*<<< orphan*/  GX_Begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_Color4u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_DIRECT ; 
 int /*<<< orphan*/  GX_DrawDone () ; 
 int /*<<< orphan*/  GX_End () ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  GX_MODULATE ; 
 int /*<<< orphan*/  GX_NONE ; 
 int /*<<< orphan*/  GX_PASSCLR ; 
 int /*<<< orphan*/  GX_Position2s16 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GX_QUADS ; 
 int /*<<< orphan*/  GX_SetTevOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetVtxDesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_TEVSTAGE0 ; 
 int /*<<< orphan*/  GX_VA_TEX0 ; 
 int /*<<< orphan*/  GX_VTXFMT0 ; 
 TYPE_2__* vmode ; 

void gxDrawRectangle(s32 x, s32 y, s32 w, s32 h, u8 alpha, GXColor color)
{
  /* GX only use Color channel for rendering */
  GX_SetTevOp (GX_TEVSTAGE0, GX_PASSCLR);
  GX_SetVtxDesc (GX_VA_TEX0, GX_NONE);
  GX_Flush();

  /* vertex coordinate */
  x -= (vmode->fbWidth/2);
  y -= (vmode->efbHeight/2);

  /* draw colored quad */
  GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
  GX_Position2s16(x,y+h);
  GX_Color4u8(color.r,color.g,color.b,alpha);
  GX_Position2s16(x+w,y+h);
  GX_Color4u8(color.r,color.g,color.b,alpha);
  GX_Position2s16(x+w,y);
  GX_Color4u8(color.r,color.g,color.b,alpha);
  GX_Position2s16(x,y);
  GX_Color4u8(color.r,color.g,color.b,alpha);
  GX_End();
  GX_DrawDone();

  /* restore GX rendering */
  GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
  GX_SetTevOp (GX_TEVSTAGE0, GX_MODULATE);
  GX_Flush();
}