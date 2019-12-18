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
typedef  int uint_t ;

/* Variables and functions */
 int REX_B ; 
 int REX_R ; 

__attribute__((used)) static void
dtrace_rex_adjust(uint_t rex_prefix, uint_t mode, uint_t *reg, uint_t *r_m)
{
#pragma unused (mode)
	if (reg != NULL && r_m == NULL) {
		if (rex_prefix & REX_B)
			*reg += 8;
	} else {
		if (reg != NULL && (REX_R & rex_prefix) != 0)
			*reg += 8;
		if (r_m != NULL && (REX_B & rex_prefix) != 0)
			*r_m += 8;
	}
}