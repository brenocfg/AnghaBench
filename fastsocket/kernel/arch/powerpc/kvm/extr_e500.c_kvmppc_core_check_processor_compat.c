#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cpu_name; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 TYPE_1__* cur_cpu_spec ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int kvmppc_core_check_processor_compat(void)
{
	int r;

	if (strcmp(cur_cpu_spec->cpu_name, "e500v2") == 0)
		r = 0;
	else
		r = -ENOTSUPP;

	return r;
}