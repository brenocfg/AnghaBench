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
typedef  int s32 ;
struct TYPE_5__ {int cell_width; int cell_height; } ;
struct TYPE_4__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  int /*<<< orphan*/  GXTexObj ;
typedef  TYPE_1__ GXColor ;

/* Variables and functions */
 int /*<<< orphan*/  DCFlushRange (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_Begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_CLAMP ; 
 int /*<<< orphan*/  GX_Color4u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GX_DrawDone () ; 
 int /*<<< orphan*/  GX_End () ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_InitTexObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_InvalidateTexAll () ; 
 int /*<<< orphan*/  GX_LoadTexObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_Position2s16 (int,int) ; 
 int /*<<< orphan*/  GX_QUADS ; 
 int /*<<< orphan*/  GX_TEXMAP0 ; 
 int /*<<< orphan*/  GX_TF_I4 ; 
 int /*<<< orphan*/  GX_TexCoord2f32 (double,double) ; 
 int /*<<< orphan*/  GX_VTXFMT0 ; 
 int /*<<< orphan*/  GetFontTexel (unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* fontHeader ; 
 int /*<<< orphan*/  fontTexture ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void DrawChar(unsigned char c, int xpos, int ypos, int size, GXColor color)
{
  /* reintialize texture object */
  GXTexObj texobj;
  GX_InitTexObj(&texobj, fontTexture, fontHeader->cell_width, fontHeader->cell_height, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
  GX_LoadTexObj(&texobj, GX_TEXMAP0);

  /* reinitialize font texture data */
  memset(fontTexture,0,fontHeader->cell_width * fontHeader->cell_height / 2);
  GetFontTexel(c,fontTexture,0,fontHeader->cell_width/2);
  DCFlushRange(fontTexture, fontHeader->cell_width * fontHeader->cell_height / 2);
  GX_InvalidateTexAll();

  /* adjust texture width */
  s32 width = (fontHeader->cell_width * size) / fontHeader->cell_height;

  /* GX rendering */
  GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
  GX_Position2s16(xpos, ypos - size);
  GX_Color4u8(color.r, color.g, color.b, 0xff);
  GX_TexCoord2f32(0.0, 0.0);
  GX_Position2s16(xpos + width, ypos - size);
  GX_Color4u8(color.r, color.g, color.b, 0xff);
  GX_TexCoord2f32(1.0, 0.0);
  GX_Position2s16(xpos + width, ypos);
  GX_Color4u8(color.r, color.g, color.b, 0xff);
  GX_TexCoord2f32(1.0, 1.0);
  GX_Position2s16(xpos, ypos);
  GX_Color4u8(color.r, color.g, color.b, 0xff);
  GX_TexCoord2f32(0.0, 1.0);
  GX_End();
  GX_DrawDone();
}