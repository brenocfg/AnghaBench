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
typedef  int /*<<< orphan*/  csh ;

/* Variables and functions */
 unsigned int ARR_SIZE (char const**) ; 
 char const** s_reg_names ; 

const char* M68K_reg_name(csh handle, unsigned int reg)
{
#ifdef CAPSTONE_DIET
	return NULL;
#else
	if (reg >= ARR_SIZE(s_reg_names)) {
		return NULL;
	}
	return s_reg_names[(int)reg];
#endif
}