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
 int /*<<< orphan*/  machine__destroy_kernel_maps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  machines__destroy_guest_kernel_maps (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_session__destroy_kernel_maps(struct perf_session *self)
{
	machine__destroy_kernel_maps(&self->host_machine);
	machines__destroy_guest_kernel_maps(&self->machines);
}