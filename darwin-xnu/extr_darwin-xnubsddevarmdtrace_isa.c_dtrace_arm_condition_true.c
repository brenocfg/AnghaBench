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

/* Variables and functions */
 int PSR_CF ; 
 int PSR_NF ; 
 int PSR_VF ; 
 int PSR_ZF ; 

int
dtrace_arm_condition_true(int cond, int cpsr)
{
	int taken = 0;
	int zf = (cpsr & PSR_ZF) ? 1 : 0,
	    nf = (cpsr & PSR_NF) ? 1 : 0,
	    cf = (cpsr & PSR_CF) ? 1 : 0,
	    vf = (cpsr & PSR_VF) ? 1 : 0;

	switch(cond) {
		case 0: taken = zf; break;
		case 1: taken = !zf; break;
		case 2: taken = cf; break;
		case 3: taken = !cf; break;
		case 4: taken = nf; break;
		case 5: taken = !nf; break;
		case 6: taken = vf; break;
		case 7: taken = !vf; break;
		case 8: taken = (cf && !zf); break;
		case 9: taken = (!cf || zf); break;
		case 10: taken = (nf == vf); break;
		case 11: taken = (nf != vf); break;
		case 12: taken = (!zf && (nf == vf)); break;
		case 13: taken = (zf || (nf != vf)); break;
		case 14: taken = 1; break;
		case 15: taken = 1; break; /* always "true" for ARM, unpredictable for THUMB. */
	}

	return taken;
}