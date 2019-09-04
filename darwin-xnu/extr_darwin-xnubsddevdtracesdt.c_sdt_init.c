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
 int /*<<< orphan*/  SDT_MAJOR ; 
 int cdevsw_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_sdt_probes_restricted () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sdt_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdt_cdevsw ; 

void sdt_init( void )
{
	int majdevno = cdevsw_add(SDT_MAJOR, &sdt_cdevsw);
		
	if (majdevno < 0) {
		printf("sdt_init: failed to allocate a major number!\n");
		return;
	}

	if (dtrace_sdt_probes_restricted()) {
		return;
	}

	sdt_attach((dev_info_t*)(uintptr_t)majdevno);
}