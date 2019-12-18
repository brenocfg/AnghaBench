#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pm_phase; int am_phase; int /*<<< orphan*/  lfo_pm; int /*<<< orphan*/  lfo_am; } ;
typedef  TYPE_1__ OPLL ;

/* Variables and functions */
 scalar_t__ AM_DP_BITS ; 
 int AM_DP_WIDTH ; 
 scalar_t__ AM_PG_BITS ; 
 size_t HIGHBITS (int,scalar_t__) ; 
 scalar_t__ PM_DP_BITS ; 
 int PM_DP_WIDTH ; 
 scalar_t__ PM_PG_BITS ; 
 int am_dphase ; 
 int /*<<< orphan*/ * amtable ; 
 int pm_dphase ; 
 int /*<<< orphan*/ * pmtable ; 

__attribute__((used)) static void update_ampm(OPLL * opll) {
	opll->pm_phase = (opll->pm_phase + pm_dphase) & (PM_DP_WIDTH - 1);
	opll->am_phase = (opll->am_phase + am_dphase) & (AM_DP_WIDTH - 1);
	opll->lfo_am = amtable[HIGHBITS(opll->am_phase, AM_DP_BITS - AM_PG_BITS)];
	opll->lfo_pm = pmtable[HIGHBITS(opll->pm_phase, PM_DP_BITS - PM_PG_BITS)];
}