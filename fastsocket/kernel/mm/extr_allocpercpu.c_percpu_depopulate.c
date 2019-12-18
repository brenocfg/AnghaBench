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
struct percpu_data {int /*<<< orphan*/ ** ptrs; } ;

/* Variables and functions */
 struct percpu_data* __percpu_disguise (void*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void percpu_depopulate(void *__pdata, int cpu)
{
	struct percpu_data *pdata = __percpu_disguise(__pdata);

	kfree(pdata->ptrs[cpu]);
	pdata->ptrs[cpu] = NULL;
}