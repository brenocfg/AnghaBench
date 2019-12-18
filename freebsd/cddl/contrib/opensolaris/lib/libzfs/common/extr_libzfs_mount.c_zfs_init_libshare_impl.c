#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * libzfs_sharehdl; } ;
typedef  TYPE_1__ libzfs_handle_t ;

/* Variables and functions */
 int SA_NO_MEMORY ; 
 int SA_OK ; 
 int /*<<< orphan*/ * _sa_init ; 
 void* _sa_init_arg (int,void*) ; 
 scalar_t__ _sa_needs_refresh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_uninit_libshare (TYPE_1__*) ; 

__attribute__((used)) static int
zfs_init_libshare_impl(libzfs_handle_t *zhandle, int service, void *arg)
{
#ifdef illumos
	/*
	 * libshare is either not installed or we're in a branded zone. The
	 * rest of the wrapper functions around the libshare calls already
	 * handle NULL function pointers, but we don't want the callers of
	 * zfs_init_libshare() to fail prematurely if libshare is not available.
	 */
	if (_sa_init == NULL)
		return (SA_OK);

	/*
	 * Attempt to refresh libshare. This is necessary if there was a cache
	 * miss for a new ZFS dataset that was just created, or if state of the
	 * sharetab file has changed since libshare was last initialized. We
	 * want to make sure so check timestamps to see if a different process
	 * has updated any of the configuration. If there was some non-ZFS
	 * change, we need to re-initialize the internal cache.
	 */
	if (_sa_needs_refresh != NULL &&
	    _sa_needs_refresh(zhandle->libzfs_sharehdl)) {
		zfs_uninit_libshare(zhandle);
		zhandle->libzfs_sharehdl = _sa_init_arg(service, arg);
	}

	if (zhandle && zhandle->libzfs_sharehdl == NULL)
		zhandle->libzfs_sharehdl = _sa_init_arg(service, arg);

	if (zhandle->libzfs_sharehdl == NULL)
		return (SA_NO_MEMORY);
#endif

	return (SA_OK);
}