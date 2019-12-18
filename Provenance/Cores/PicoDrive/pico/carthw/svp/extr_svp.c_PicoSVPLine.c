#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int scanline; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int POPT_EN_DRC ; 
 TYPE_2__ Pico ; 
 int PicoOpt ; 
 int PicoSVPCycles ; 
 int /*<<< orphan*/  ssp1601_dyn_run (int) ; 
 int /*<<< orphan*/  ssp1601_run (int) ; 
 scalar_t__ svp_dyn_ready ; 

__attribute__((used)) static void PicoSVPLine(void)
{
	int count = 1;
#if defined(__arm__) || defined(PSP)
	// performance hack
	static int delay_lines = 0;
	delay_lines++;
	if ((Pico.m.scanline&0xf) != 0xf && Pico.m.scanline != 261 && Pico.m.scanline != 311)
		return;
	count = delay_lines;
	delay_lines = 0;
#endif

#ifdef _SVP_DRC
	if ((PicoOpt & POPT_EN_DRC) && svp_dyn_ready)
		ssp1601_dyn_run(PicoSVPCycles * count);
	else
#endif
	{
		ssp1601_run(PicoSVPCycles * count);
		svp_dyn_ready = 0; // just in case
	}

	// test mode
	//if (Pico.m.frame_count == 13) PicoPad[0] |= 0xff;
}