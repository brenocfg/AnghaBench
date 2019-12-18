#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* zpool_next; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_9__ {TYPE_3__* zfs_hdl; } ;
typedef  TYPE_2__ zfs_handle_t ;
struct TYPE_10__ {TYPE_1__* libzfs_pool_handles; } ;
typedef  TYPE_3__ libzfs_handle_t ;

/* Variables and functions */
 TYPE_1__* zpool_open_canfail (TYPE_3__*,char const*) ; 

__attribute__((used)) static zpool_handle_t *
zpool_add_handle(zfs_handle_t *zhp, const char *pool_name)
{
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	zpool_handle_t *zph;

	if ((zph = zpool_open_canfail(hdl, pool_name)) != NULL) {
		if (hdl->libzfs_pool_handles != NULL)
			zph->zpool_next = hdl->libzfs_pool_handles;
		hdl->libzfs_pool_handles = zph;
	}
	return (zph);
}