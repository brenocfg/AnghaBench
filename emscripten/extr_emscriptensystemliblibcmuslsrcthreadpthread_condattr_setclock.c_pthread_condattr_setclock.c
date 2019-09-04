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
struct TYPE_3__ {int __attr; } ;
typedef  TYPE_1__ pthread_condattr_t ;
typedef  unsigned int clockid_t ;

/* Variables and functions */
 int EINVAL ; 

int pthread_condattr_setclock(pthread_condattr_t *a, clockid_t clk)
{
	if (clk < 0 || clk-2U < 2) return EINVAL;
	a->__attr &= 0x80000000;
	a->__attr |= clk;
	return 0;
}