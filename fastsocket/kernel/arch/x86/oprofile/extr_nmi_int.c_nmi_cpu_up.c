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
 int /*<<< orphan*/  nmi_cpu_setup (void*) ; 
 int /*<<< orphan*/  nmi_cpu_start (void*) ; 
 scalar_t__ nmi_enabled ; 

__attribute__((used)) static void nmi_cpu_up(void *dummy)
{
	if (nmi_enabled)
		nmi_cpu_setup(dummy);
	if (ctr_running)
		nmi_cpu_start(dummy);
}