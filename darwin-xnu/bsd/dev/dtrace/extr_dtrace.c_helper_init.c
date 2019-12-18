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
 int /*<<< orphan*/  DEVFS_CHAR ; 
 int /*<<< orphan*/  DTRACEMNR_HELPER ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  HELPER_MAJOR ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ cdevsw_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devfs_make_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gDTraceInited ; 
 int /*<<< orphan*/  helper_cdevsw ; 
 scalar_t__ helper_majdevno ; 
 int /*<<< orphan*/  makedev (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
helper_init( void )
{
	/*
	 * Once the "helper" is initialized, it can take ioctl calls that use locks
	 * and zones initialized in dtrace_init. Make certain dtrace_init was called
	 * before us.
	 */

	if (!gDTraceInited) {
		panic("helper_init before dtrace_init\n");
	}

	if (0 >= helper_majdevno)
	{
		helper_majdevno = cdevsw_add(HELPER_MAJOR, &helper_cdevsw);
		
		if (helper_majdevno < 0) {
			printf("helper_init: failed to allocate a major number!\n");
			return;
		}
		
		if (NULL == devfs_make_node( makedev(helper_majdevno, 0), DEVFS_CHAR, UID_ROOT, GID_WHEEL, 0666, 
					DTRACEMNR_HELPER, 0 )) {
			printf("dtrace_init: failed to devfs_make_node for helper!\n");
			return;
		}
	} else
		panic("helper_init: called twice!\n");
}