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
struct TYPE_5__ {struct TYPE_5__* zpool_next; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_6__ {TYPE_1__* libzfs_pool_handles; } ;
typedef  TYPE_2__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  zpool_close (TYPE_1__*) ; 

void
zpool_free_handles(libzfs_handle_t *hdl)
{
	zpool_handle_t *next, *zph = hdl->libzfs_pool_handles;

	while (zph != NULL) {
		next = zph->zpool_next;
		zpool_close(zph);
		zph = next;
	}
	hdl->libzfs_pool_handles = NULL;
}