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
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int zfs_init_libshare_impl (int /*<<< orphan*/ *,int,void*) ; 

int
zfs_init_libshare_arg(libzfs_handle_t *zhandle, int service, void *arg)
{
	return (zfs_init_libshare_impl(zhandle, service, arg));
}