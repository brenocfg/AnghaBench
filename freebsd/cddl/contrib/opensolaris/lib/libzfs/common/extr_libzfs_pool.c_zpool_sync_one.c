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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_add_boolean_value (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int lzc_sync (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_handle (int /*<<< orphan*/ *) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 int zpool_standard_error_fmt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const*) ; 

int
zpool_sync_one(zpool_handle_t *zhp, void *data)
{
	int ret;
	libzfs_handle_t *hdl = zpool_get_handle(zhp);
	const char *pool_name = zpool_get_name(zhp);
	boolean_t *force = data;
	nvlist_t *innvl = fnvlist_alloc();

	fnvlist_add_boolean_value(innvl, "force", *force);
	if ((ret = lzc_sync(pool_name, innvl, NULL)) != 0) {
		nvlist_free(innvl);
		return (zpool_standard_error_fmt(hdl, ret,
		    dgettext(TEXT_DOMAIN, "sync '%s' failed"), pool_name));
	}
	nvlist_free(innvl);

	return (0);
}