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
 int T1_SIG_OTH ; 
 char* lut_ctxno_zc ; 

__attribute__((used)) static char t1_getctxno_zc(int f, int orient) {
	return lut_ctxno_zc[(orient << 8) | (f & T1_SIG_OTH)];
}