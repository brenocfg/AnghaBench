#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  verstr ;
struct TYPE_2__ {int cb_version; int /*<<< orphan*/  cb_numsamegraded; int /*<<< orphan*/  cb_numfailed; scalar_t__* cb_lastfs; int /*<<< orphan*/  cb_numupgraded; } ;
typedef  TYPE_1__ upgrade_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  ZFS_PROP_VERSION ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  history_str ; 
 int /*<<< orphan*/  log_history ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  same_pool (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char*) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 int zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_set (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ zfs_spa_version (int /*<<< orphan*/ *,int*) ; 
 int zfs_spa_version_map (int) ; 
 int /*<<< orphan*/  zpool_log_history (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
upgrade_set_callback(zfs_handle_t *zhp, void *data)
{
	upgrade_cbdata_t *cb = data;
	int version = zfs_prop_get_int(zhp, ZFS_PROP_VERSION);
	int needed_spa_version;
	int spa_version;

	if (zfs_spa_version(zhp, &spa_version) < 0)
		return (-1);

	needed_spa_version = zfs_spa_version_map(cb->cb_version);

	if (needed_spa_version < 0)
		return (-1);

	if (spa_version < needed_spa_version) {
		/* can't upgrade */
		(void) printf(gettext("%s: can not be "
		    "upgraded; the pool version needs to first "
		    "be upgraded\nto version %d\n\n"),
		    zfs_get_name(zhp), needed_spa_version);
		cb->cb_numfailed++;
		return (0);
	}

	/* upgrade */
	if (version < cb->cb_version) {
		char verstr[16];
		(void) snprintf(verstr, sizeof (verstr),
		    "%llu", cb->cb_version);
		if (cb->cb_lastfs[0] && !same_pool(zhp, cb->cb_lastfs)) {
			/*
			 * If they did "zfs upgrade -a", then we could
			 * be doing ioctls to different pools.  We need
			 * to log this history once to each pool, and bypass
			 * the normal history logging that happens in main().
			 */
			(void) zpool_log_history(g_zfs, history_str);
			log_history = B_FALSE;
		}
		if (zfs_prop_set(zhp, "version", verstr) == 0)
			cb->cb_numupgraded++;
		else
			cb->cb_numfailed++;
		(void) strcpy(cb->cb_lastfs, zfs_get_name(zhp));
	} else if (version > cb->cb_version) {
		/* can't downgrade */
		(void) printf(gettext("%s: can not be downgraded; "
		    "it is already at version %u\n"),
		    zfs_get_name(zhp), version);
		cb->cb_numfailed++;
	} else {
		cb->cb_numsamegraded++;
	}
	return (0);
}