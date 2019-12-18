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
struct TYPE_3__ {scalar_t__ zfs_recvd_props; scalar_t__ zfs_props; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */

__attribute__((used)) static void
zfs_set_recvd_props_mode(zfs_handle_t *zhp, uint64_t *cookie)
{
	*cookie = (uint64_t)(uintptr_t)zhp->zfs_props;
	zhp->zfs_props = zhp->zfs_recvd_props;
}