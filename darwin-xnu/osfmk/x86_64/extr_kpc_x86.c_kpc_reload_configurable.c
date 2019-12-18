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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIGURABLE_RELOAD (int) ; 
 int IA32_PERFEVTSEL_EN ; 
 int IA32_PERFEVTSELx (int) ; 
 int IA32_PMCx (int) ; 
 int /*<<< orphan*/  wrIA32_PERFEVTSELx (int,int) ; 
 int /*<<< orphan*/  wrIA32_PMCx (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
kpc_reload_configurable(int ctr)
{
	uint64_t cfg = IA32_PERFEVTSELx(ctr);

	/* counters must be disabled before they can be written to */
	uint64_t old = IA32_PMCx(ctr);
	wrIA32_PERFEVTSELx(ctr, cfg & ~IA32_PERFEVTSEL_EN);
	wrIA32_PMCx(ctr, CONFIGURABLE_RELOAD(ctr));
	wrIA32_PERFEVTSELx(ctr, cfg);
	return old;
}