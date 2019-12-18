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
struct perf_session {int /*<<< orphan*/  machines; int /*<<< orphan*/  host_machine; } ;

/* Variables and functions */
 int machine__create_kernel_maps (int /*<<< orphan*/ *) ; 
 int machines__create_guest_kernel_maps (int /*<<< orphan*/ *) ; 

int perf_session__create_kernel_maps(struct perf_session *self)
{
	int ret = machine__create_kernel_maps(&self->host_machine);

	if (ret >= 0)
		ret = machines__create_guest_kernel_maps(&self->machines);
	return ret;
}