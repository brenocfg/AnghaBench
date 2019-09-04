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
typedef  int /*<<< orphan*/  dev_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYSTRACE_MAJOR ; 
 int cdevsw_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_sdt_probes_restricted () ; 
 int /*<<< orphan*/  machtrace_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  systrace_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systrace_cdevsw ; 

void systrace_init( void )
{
	if (dtrace_sdt_probes_restricted()) {
		return;
	}

	int majdevno = cdevsw_add(SYSTRACE_MAJOR, &systrace_cdevsw);

	if (majdevno < 0) {
		printf("systrace_init: failed to allocate a major number!\n");
		return;
	}

	systrace_attach((dev_info_t*)(uintptr_t)majdevno);
	machtrace_attach((dev_info_t*)(uintptr_t)majdevno);
}