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
typedef  int /*<<< orphan*/  cnd_t ;

/* Variables and functions */
 int __private_cond_signal (int /*<<< orphan*/ *,int) ; 

int cnd_signal(cnd_t *c)
{
	/* This internal function never fails, and always returns zero,
	 * which matches the value thrd_success is defined with. */
	return __private_cond_signal(c, 1);
}