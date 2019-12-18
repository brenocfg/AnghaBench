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
struct TYPE_4__ {scalar_t__ rom; } ;
struct TYPE_3__ {int /*<<< orphan*/  ssp1601; scalar_t__ iram_rom; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_SVP ; 
 int POPT_EN_DRC ; 
 TYPE_2__ Pico ; 
 int PicoOpt ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ssp1601_dyn_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssp1601_reset (int /*<<< orphan*/ *) ; 
 TYPE_1__* svp ; 
 scalar_t__ svp_dyn_ready ; 

__attribute__((used)) static void PicoSVPReset(void)
{
	elprintf(EL_SVP, "SVP reset");

	memcpy(svp->iram_rom + 0x800, Pico.rom + 0x800, 0x20000 - 0x800);
	ssp1601_reset(&svp->ssp1601);
#ifdef _SVP_DRC
	if ((PicoOpt & POPT_EN_DRC) && svp_dyn_ready)
		ssp1601_dyn_reset(&svp->ssp1601);
#endif
}