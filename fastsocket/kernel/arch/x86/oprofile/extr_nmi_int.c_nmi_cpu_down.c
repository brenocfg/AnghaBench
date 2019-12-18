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
 scalar_t__ ctr_running ; 
 int /*<<< orphan*/  nmi_cpu_shutdown (void*) ; 
 int /*<<< orphan*/  nmi_cpu_stop (void*) ; 
 scalar_t__ nmi_enabled ; 

__attribute__((used)) static void nmi_cpu_down(void *dummy)
{
	if (ctr_running)
		nmi_cpu_stop(dummy);
	if (nmi_enabled)
		nmi_cpu_shutdown(dummy);
}