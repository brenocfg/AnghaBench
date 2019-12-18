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
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_LOG ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_import_config (char*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  print_status_config (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* zpool_vdev_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_logs(zpool_handle_t *zhp, nvlist_t *nv, int namewidth, boolean_t verbose)
{
	uint_t c, children;
	nvlist_t **child;

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_CHILDREN, &child,
	    &children) != 0)
		return;

	(void) printf(gettext("\tlogs\n"));

	for (c = 0; c < children; c++) {
		uint64_t is_log = B_FALSE;
		char *name;

		(void) nvlist_lookup_uint64(child[c], ZPOOL_CONFIG_IS_LOG,
		    &is_log);
		if (!is_log)
			continue;
		name = zpool_vdev_name(g_zfs, zhp, child[c], B_TRUE);
		if (verbose)
			print_status_config(zhp, name, child[c], namewidth,
			    2, B_FALSE);
		else
			print_import_config(name, child[c], namewidth, 2);
		free(name);
	}
}