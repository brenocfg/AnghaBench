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
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_2__ {scalar_t__ cb_version; int /*<<< orphan*/  cb_poolname; void* cb_first; void* cb_unavail; } ;
typedef  TYPE_1__ upgrade_cbdata_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 scalar_t__ POOL_STATE_UNAVAIL ; 
 scalar_t__ SPA_VERSION_FEATURES ; 
 int /*<<< orphan*/  SPA_VERSION_IS_SUPPORTED (scalar_t__) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VERSION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  history_str ; 
 void* log_history ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  root_pool_upgrade_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int upgrade_enable_all (int /*<<< orphan*/ *,int*) ; 
 int upgrade_version (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_log_history (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
upgrade_cb(zpool_handle_t *zhp, void *arg)
{
	upgrade_cbdata_t *cbp = arg;
	nvlist_t *config;
	uint64_t version;
	boolean_t printnl = B_FALSE;
	int ret;

	if (zpool_get_state(zhp) == POOL_STATE_UNAVAIL) {
		(void) fprintf(stderr, gettext("cannot upgrade '%s': pool is "
		    "currently unavailable.\n\n"), zpool_get_name(zhp));
		cbp->cb_unavail = B_TRUE;
		/* Allow iteration to continue. */
		return (0);
	}

	config = zpool_get_config(zhp, NULL);
	verify(nvlist_lookup_uint64(config, ZPOOL_CONFIG_VERSION,
	    &version) == 0);

	assert(SPA_VERSION_IS_SUPPORTED(version));

	if (version < cbp->cb_version) {
		cbp->cb_first = B_FALSE;
		ret = upgrade_version(zhp, cbp->cb_version);
		if (ret != 0)
			return (ret);
#ifdef __FreeBSD__
		root_pool_upgrade_check(zhp, cbp->cb_poolname,
		    sizeof(cbp->cb_poolname));
#endif	/* __FreeBSD__ */
		printnl = B_TRUE;

#ifdef illumos
		/*
		 * If they did "zpool upgrade -a", then we could
		 * be doing ioctls to different pools.  We need
		 * to log this history once to each pool, and bypass
		 * the normal history logging that happens in main().
		 */
		(void) zpool_log_history(g_zfs, history_str);
		log_history = B_FALSE;
#endif
	}

	if (cbp->cb_version >= SPA_VERSION_FEATURES) {
		int count;
		ret = upgrade_enable_all(zhp, &count);
		if (ret != 0)
			return (ret);

		if (count > 0) {
			cbp->cb_first = B_FALSE;
			printnl = B_TRUE;
#ifdef __FreeBSD__
			root_pool_upgrade_check(zhp, cbp->cb_poolname,
			    sizeof(cbp->cb_poolname));
#endif	/* __FreeBSD__ */
			/*
			 * If they did "zpool upgrade -a", then we could
			 * be doing ioctls to different pools.  We need
			 * to log this history once to each pool, and bypass
			 * the normal history logging that happens in main().
			 */
			(void) zpool_log_history(g_zfs, history_str);
			log_history = B_FALSE;
		}
	}

	if (printnl) {
		(void) printf(gettext("\n"));
	}

	return (0);
}