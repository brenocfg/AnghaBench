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
typedef  int u32 ;

/* Variables and functions */
 int PMGC0_FAC ; 
 int PMGC0_FCECE ; 
 int PMGC0_PMIE ; 
 int /*<<< orphan*/  PMRN_PMGC0 ; 
 int mfpmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pmc_stop_ctrs(void)
{
	u32 pmgc0 = mfpmr(PMRN_PMGC0);

	pmgc0 |= PMGC0_FAC;

	pmgc0 &= ~(PMGC0_PMIE | PMGC0_FCECE);

	mtpmr(PMRN_PMGC0, pmgc0);
}