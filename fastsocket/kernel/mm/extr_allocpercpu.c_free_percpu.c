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
 int /*<<< orphan*/  __percpu_depopulate_mask (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __percpu_disguise (void*) ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void free_percpu(void *__pdata)
{
	if (unlikely(!__pdata))
		return;
	__percpu_depopulate_mask(__pdata, cpu_possible_mask);
	kfree(__percpu_disguise(__pdata));
}