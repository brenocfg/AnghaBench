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
struct smd_half_channel {int fDSR; int fCTS; int fCD; unsigned int state; int fSTATE; } ;

/* Variables and functions */
 unsigned int SMD_SS_OPENED ; 
 int /*<<< orphan*/  notify_other_smd () ; 

__attribute__((used)) static void hc_set_state(volatile struct smd_half_channel *hc, unsigned n)
{
	if (n == SMD_SS_OPENED) {
		hc->fDSR = 1;
		hc->fCTS = 1;
		hc->fCD = 1;
	} else {
		hc->fDSR = 0;
		hc->fCTS = 0;
		hc->fCD = 0;
	}
	hc->state = n;
	hc->fSTATE = 1;
	notify_other_smd();
}