#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ zfs_type; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_6__ {int /*<<< orphan*/  holdtag; int /*<<< orphan*/ * snapholds; } ;
typedef  TYPE_2__ send_dump_data_t ;

/* Variables and functions */
 scalar_t__ ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gather_holds(zfs_handle_t *zhp, send_dump_data_t *sdd)
{
	assert(zhp->zfs_type == ZFS_TYPE_SNAPSHOT);

	/*
	 * zfs_send() only sets snapholds for sends that need them,
	 * e.g. replication and doall.
	 */
	if (sdd->snapholds == NULL)
		return;

	fnvlist_add_string(sdd->snapholds, zhp->zfs_name, sdd->holdtag);
}