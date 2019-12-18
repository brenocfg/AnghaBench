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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dirtyPal; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {scalar_t__ scaling; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmuScanSlowBegin ; 
 int /*<<< orphan*/  EmuScanSlowEnd ; 
 int /*<<< orphan*/  GU_DIRECT ; 
 int /*<<< orphan*/  GU_LINEAR ; 
 int /*<<< orphan*/  GU_NEAREST ; 
 int /*<<< orphan*/  GU_PSM_5650 ; 
 int /*<<< orphan*/  GU_PSM_T8 ; 
 int /*<<< orphan*/  GU_TCC_RGB ; 
 int /*<<< orphan*/  GU_TFX_REPLACE ; 
 int /*<<< orphan*/  PDF_NONE ; 
 TYPE_3__ Pico ; 
 int /*<<< orphan*/  PicoDrawSetCallbacks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoDrawSetOutFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VRAM_STUFF ; 
 scalar_t__ blit_16bit_mode ; 
 TYPE_2__ currentConfig ; 
 scalar_t__ dynamic_palette ; 
 int /*<<< orphan*/  guCmdList ; 
 int* localPal ; 
 int /*<<< orphan*/  sceGuClutMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuFinish () ; 
 int /*<<< orphan*/  sceGuStart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTexFilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTexFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTexImage (int /*<<< orphan*/ ,int,int,int,char*) ; 
 int /*<<< orphan*/  sceGuTexMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGuTexOffset (float,float) ; 
 int /*<<< orphan*/  sceGuTexScale (float,float) ; 
 int /*<<< orphan*/  set_scaling_params () ; 

__attribute__((used)) static void vidResetMode(void)
{
	// setup GU
	sceGuSync(0,0); // sync with prev
	sceGuStart(GU_DIRECT, guCmdList);

	sceGuClutMode(GU_PSM_5650,0,0xff,0);
	sceGuTexMode(GU_PSM_T8,0,0,0); // 8-bit image
	sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGB);
	if (currentConfig.scaling)
	     sceGuTexFilter(GU_LINEAR, GU_LINEAR);
	else sceGuTexFilter(GU_NEAREST, GU_NEAREST);
	sceGuTexScale(1.0f,1.0f);
	sceGuTexOffset(0.0f,0.0f);

	sceGuTexImage(0,512,512,512,(char *)VRAM_STUFF + 16);

	// slow rend.
	PicoDrawSetOutFormat(PDF_NONE, 0);
	PicoDrawSetCallbacks(EmuScanSlowBegin, EmuScanSlowEnd);

	localPal[0xe0] = 0;
	localPal[0xf0] = 0x001f;
	Pico.m.dirtyPal = 1;
	blit_16bit_mode = dynamic_palette = 0;

	sceGuFinish();
	set_scaling_params();
	sceGuSync(0,0);
}