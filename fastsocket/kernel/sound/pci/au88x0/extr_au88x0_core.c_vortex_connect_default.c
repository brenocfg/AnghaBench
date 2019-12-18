#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void** mixspdif; int /*<<< orphan*/  fixed_res; void** mixcapt; void** mixplayb; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_SPDIFOUT (int) ; 
 int /*<<< orphan*/  MIX_CAPT (int) ; 
 scalar_t__ VORTEX_IS_QUAD (TYPE_1__*) ; 
 int /*<<< orphan*/  VORTEX_RESOURCE_MIXIN ; 
 int /*<<< orphan*/  VORTEX_RESOURCE_MIXOUT ; 
 int /*<<< orphan*/  vortex_Vort3D_connect (TYPE_1__*,int) ; 
 void* vortex_adb_checkinout (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_connect_codecplay (TYPE_1__*,int,void**) ; 
 int /*<<< orphan*/  vortex_connect_codecrec (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_connection_mix_adb (TYPE_1__*,int,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_wt_connect (TYPE_1__*,int) ; 

__attribute__((used)) static void vortex_connect_default(vortex_t * vortex, int en)
{
	// Connect AC97 codec.
	vortex->mixplayb[0] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXOUT);
	vortex->mixplayb[1] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXOUT);
	if (VORTEX_IS_QUAD(vortex)) {
		vortex->mixplayb[2] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
					  VORTEX_RESOURCE_MIXOUT);
		vortex->mixplayb[3] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
					  VORTEX_RESOURCE_MIXOUT);
	}
	vortex_connect_codecplay(vortex, en, vortex->mixplayb);

	vortex->mixcapt[0] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXIN);
	vortex->mixcapt[1] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXIN);
	vortex_connect_codecrec(vortex, en, MIX_CAPT(0), MIX_CAPT(1));

	// Connect SPDIF
#ifndef CHIP_AU8820
	vortex->mixspdif[0] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXOUT);
	vortex->mixspdif[1] = vortex_adb_checkinout(vortex, vortex->fixed_res, en,
				  VORTEX_RESOURCE_MIXOUT);
	vortex_connection_mix_adb(vortex, en, 0x14, vortex->mixspdif[0],
				  ADB_SPDIFOUT(0));
	vortex_connection_mix_adb(vortex, en, 0x14, vortex->mixspdif[1],
				  ADB_SPDIFOUT(1));
#endif
	// Connect WT
#ifndef CHIP_AU8810
	vortex_wt_connect(vortex, en);
#endif
	// A3D (crosstalk canceler and A3D slices). AU8810 disabled for now.
#ifndef CHIP_AU8820
	vortex_Vort3D_connect(vortex, en);
#endif
	// Connect I2S

	// Connect DSP interface for SQ3500 turbo (not here i think...)

	// Connect AC98 modem codec
	
}