#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* devfs_event_log_t ;
struct TYPE_3__ {int /*<<< orphan*/ * del_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
devfs_release_event_log(devfs_event_log_t delp, int need_free)
{
	if (delp->del_entries == NULL) {
		panic("Free of devfs notify info that has not been intialized.\n");
	}

	if (need_free) {
		FREE(delp->del_entries, M_TEMP);
	}

	delp->del_entries = NULL;
}