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
struct TYPE_2__ {void* profc_probe; } ;
typedef  TYPE_1__ profile_probe_percpu_t ;
typedef  int /*<<< orphan*/  dtrace_cpu_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static void
profile_offline(void *arg, dtrace_cpu_t *cpu, void *oarg)
{
	profile_probe_percpu_t *pcpu = oarg;

	ASSERT(pcpu->profc_probe == arg);
#pragma unused(pcpu,arg,cpu) /* __APPLE__ */
}