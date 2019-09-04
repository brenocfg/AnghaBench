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
 int T1_CTXNO_MAG ; 
 int T1_REFINE ; 
 int T1_SIG_OTH ; 

__attribute__((used)) static int t1_getctxno_mag(int f) {
	int tmp1 = (f & T1_SIG_OTH) ? T1_CTXNO_MAG + 1 : T1_CTXNO_MAG;
	int tmp2 = (f & T1_REFINE) ? T1_CTXNO_MAG + 2 : tmp1;
	return (tmp2);
}