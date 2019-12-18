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
struct TYPE_2__ {int /*<<< orphan*/ * progress; } ;

/* Variables and functions */
 scalar_t__ initializing ; 
 TYPE_1__ ppc_md ; 

__attribute__((used)) static int pmac_late_init(void)
{
	initializing = 0;
	/* this is udbg (which is __init) and we can later use it during
	 * cpu hotplug (in smp_core99_kick_cpu) */
	ppc_md.progress = NULL;
	return 0;
}