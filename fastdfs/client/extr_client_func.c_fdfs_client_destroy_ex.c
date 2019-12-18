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
struct TYPE_3__ {scalar_t__ server_index; scalar_t__ server_count; int /*<<< orphan*/ * servers; } ;
typedef  TYPE_1__ TrackerServerGroup ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void fdfs_client_destroy_ex(TrackerServerGroup *pTrackerGroup)
{
	if (pTrackerGroup->servers != NULL)
	{
		free(pTrackerGroup->servers);
		pTrackerGroup->servers = NULL;

		pTrackerGroup->server_count = 0;
		pTrackerGroup->server_index = 0;
	}
}