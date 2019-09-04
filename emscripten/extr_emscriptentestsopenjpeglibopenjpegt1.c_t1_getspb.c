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
 int T1_SGN ; 
 int T1_SIG_PRIM ; 
 char* lut_spb ; 

__attribute__((used)) static char t1_getspb(int f) {
	return lut_spb[(f & (T1_SIG_PRIM | T1_SGN)) >> 4];
}