#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UBYTE ;
struct TYPE_12__ {int* ScreenBuffer; int ActiveBuffer; int Width; int PrimContext; int /*<<< orphan*/  EvenOrOdd; int /*<<< orphan*/  PSM; } ;
struct TYPE_11__ {int /*<<< orphan*/  FIELD; } ;
struct TYPE_10__ {int Vram; int VramClut; int /*<<< orphan*/  Filter; int /*<<< orphan*/  Clut; int /*<<< orphan*/ * Mem; int /*<<< orphan*/  PSM; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
typedef  TYPE_1__ GSTEXTURE ;
typedef  TYPE_2__ GSREG ;

/* Variables and functions */
 scalar_t__ GS_CSR ; 
 int /*<<< orphan*/  GS_FILTER_LINEAR ; 
 int /*<<< orphan*/  GS_PSM_T8 ; 
 int /*<<< orphan*/  GS_SET_DISPFB2 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Screen_HEIGHT ; 
 int /*<<< orphan*/  Screen_WIDTH ; 
 scalar_t__ Screen_atari ; 
 int /*<<< orphan*/  clut ; 
 TYPE_3__* gsGlobal ; 
 int /*<<< orphan*/  gsKit_prim_sprite_texture (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gsKit_setactive (TYPE_3__*) ; 
 int /*<<< orphan*/  gsKit_sync_flip (TYPE_3__*) ; 
 int /*<<< orphan*/  gsKit_texture_upload (TYPE_3__*,TYPE_1__*) ; 

void PLATFORM_DisplayScreen(void)
{
	GSTEXTURE tex;
	tex.Width = Screen_WIDTH;
	tex.Height = Screen_HEIGHT;
	tex.PSM = GS_PSM_T8;
	tex.Mem = (UBYTE *) Screen_atari;
	tex.Clut = clut;
	tex.Vram = 0x200000;
	tex.VramClut = 0x280000;
	tex.Filter = GS_FILTER_LINEAR;
	// TODO: upload clut just once
	gsKit_texture_upload(gsGlobal, &tex);
	gsKit_prim_sprite_texture(gsGlobal, &tex, 0, 0, 32, 0, 640, 480, 32 + 320, 240, 0, 0x80808080);
#if 0
	gsKit_sync_flip(gsGlobal);
#else
	// flip without vsync
	// this is a copy of gsKit_sync_flip() code with just gsKit_vsync() call removed
	GS_SET_DISPFB2(gsGlobal->ScreenBuffer[gsGlobal->ActiveBuffer & 1] / 8192,
		gsGlobal->Width / 64, gsGlobal->PSM, 0, 0 );
	gsGlobal->ActiveBuffer ^= 1;
	gsGlobal->PrimContext ^= 1;
	gsGlobal->EvenOrOdd = ((GSREG *) GS_CSR)->FIELD;
	gsKit_setactive(gsGlobal);
#endif

}