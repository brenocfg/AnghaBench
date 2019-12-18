#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int romsize; scalar_t__ rom; } ;
struct TYPE_7__ {int /*<<< orphan*/  ssp1601; int /*<<< orphan*/ * dram; int /*<<< orphan*/ * iram_rom; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int EL_STATUS ; 
 int EL_SVP ; 
 int /*<<< orphan*/  PAHW_SVP ; 
 int POPT_EN_DRC ; 
 TYPE_5__ Pico ; 
 int /*<<< orphan*/  PicoAHW ; 
 int /*<<< orphan*/  PicoCartMemSetup ; 
 int PicoCartResize (int) ; 
 int /*<<< orphan*/  PicoCartUnloadHook ; 
 int /*<<< orphan*/  PicoDmaHook ; 
 int /*<<< orphan*/  PicoLineHook ; 
 int PicoOpt ; 
 int /*<<< orphan*/  PicoResetHook ; 
 int /*<<< orphan*/  PicoSVPDma ; 
 int /*<<< orphan*/  PicoSVPExit ; 
 int /*<<< orphan*/  PicoSVPLine ; 
 int /*<<< orphan*/  PicoSVPMemSetup ; 
 int /*<<< orphan*/  PicoSVPReset ; 
 TYPE_1__* carthw_chunks ; 
 int /*<<< orphan*/  elprintf (int,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ssp1601_dyn_startup () ; 
 TYPE_2__* svp ; 
 int svp_dyn_ready ; 
 TYPE_1__* svp_states ; 

void PicoSVPStartup(void)
{
	int ret;

	elprintf(EL_STATUS, "SVP startup");

	ret = PicoCartResize(Pico.romsize + sizeof(*svp));
	if (ret != 0) {
		elprintf(EL_STATUS|EL_SVP, "OOM for SVP data");
		return;
	}

	svp = (void *) ((char *)Pico.rom + Pico.romsize);
	memset(svp, 0, sizeof(*svp));

	// init SVP compiler
	svp_dyn_ready = 0;
#ifdef _SVP_DRC
	if (PicoOpt & POPT_EN_DRC) {
		if (ssp1601_dyn_startup())
			return;
		svp_dyn_ready = 1;
	}
#endif

	// init ok, setup hooks..
	PicoCartMemSetup = PicoSVPMemSetup;
	PicoDmaHook = PicoSVPDma;
	PicoResetHook = PicoSVPReset;
	PicoLineHook = PicoSVPLine;
	PicoCartUnloadHook = PicoSVPExit;

	// save state stuff
	svp_states[0].ptr = svp->iram_rom;
	svp_states[1].ptr = svp->dram;
	svp_states[2].ptr = &svp->ssp1601;
	carthw_chunks = svp_states;
	PicoAHW |= PAHW_SVP;
}