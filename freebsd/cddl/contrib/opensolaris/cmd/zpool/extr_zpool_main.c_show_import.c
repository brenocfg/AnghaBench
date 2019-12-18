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
struct TYPE_2__ {scalar_t__ vs_state; scalar_t__ vs_aux; } ;
typedef  TYPE_1__ vdev_stat_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ POOL_STATE_DESTROYED ; 
 scalar_t__ POOL_STATE_EXPORTED ; 
 scalar_t__ VDEV_AUX_CORRUPT_DATA ; 
 scalar_t__ VDEV_STATE_CANT_OPEN ; 
 scalar_t__ VDEV_STATE_CLOSED ; 
 scalar_t__ VDEV_STATE_DEGRADED ; 
 scalar_t__ VDEV_STATE_HEALTHY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_COMMENT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_STATE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_STATS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
#define  ZPOOL_STATUS_BAD_GUID_SUM 146 
#define  ZPOOL_STATUS_BAD_LOG 145 
#define  ZPOOL_STATUS_CORRUPT_DATA 144 
#define  ZPOOL_STATUS_CORRUPT_LABEL_NR 143 
#define  ZPOOL_STATUS_CORRUPT_LABEL_R 142 
#define  ZPOOL_STATUS_CORRUPT_POOL 141 
#define  ZPOOL_STATUS_FAULTED_DEV_NR 140 
#define  ZPOOL_STATUS_FAULTED_DEV_R 139 
#define  ZPOOL_STATUS_FEAT_DISABLED 138 
#define  ZPOOL_STATUS_HOSTID_MISMATCH 137 
#define  ZPOOL_STATUS_MISSING_DEV_NR 136 
#define  ZPOOL_STATUS_MISSING_DEV_R 135 
#define  ZPOOL_STATUS_NON_NATIVE_ASHIFT 134 
#define  ZPOOL_STATUS_OFFLINE_DEV 133 
 int ZPOOL_STATUS_OK ; 
#define  ZPOOL_STATUS_RESILVERING 132 
#define  ZPOOL_STATUS_UNSUP_FEAT_READ 131 
#define  ZPOOL_STATUS_UNSUP_FEAT_WRITE 130 
#define  ZPOOL_STATUS_VERSION_NEWER 129 
#define  ZPOOL_STATUS_VERSION_OLDER 128 
 int /*<<< orphan*/  assert (int) ; 
 char* gettext (char*) ; 
 int max_width (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ num_logs (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ nvlist_lookup_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_import_config (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_logs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  verify (int) ; 
 int zpool_import_status (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  zpool_print_unsup_feat (int /*<<< orphan*/ *) ; 
 char* zpool_state_to_name (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
show_import(nvlist_t *config)
{
	uint64_t pool_state;
	vdev_stat_t *vs;
	char *name;
	uint64_t guid;
	char *msgid;
	nvlist_t *nvroot;
	int reason;
	const char *health;
	uint_t vsc;
	int namewidth;
	char *comment;

	verify(nvlist_lookup_string(config, ZPOOL_CONFIG_POOL_NAME,
	    &name) == 0);
	verify(nvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_GUID,
	    &guid) == 0);
	verify(nvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_STATE,
	    &pool_state) == 0);
	verify(nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
	    &nvroot) == 0);

	verify(nvlist_lookup_uint64_array(nvroot, ZPOOL_CONFIG_VDEV_STATS,
	    (uint64_t **)&vs, &vsc) == 0);
	health = zpool_state_to_name(vs->vs_state, vs->vs_aux);

	reason = zpool_import_status(config, &msgid);

	(void) printf(gettext("   pool: %s\n"), name);
	(void) printf(gettext("     id: %llu\n"), (u_longlong_t)guid);
	(void) printf(gettext("  state: %s"), health);
	if (pool_state == POOL_STATE_DESTROYED)
		(void) printf(gettext(" (DESTROYED)"));
	(void) printf("\n");

	switch (reason) {
	case ZPOOL_STATUS_MISSING_DEV_R:
	case ZPOOL_STATUS_MISSING_DEV_NR:
	case ZPOOL_STATUS_BAD_GUID_SUM:
		(void) printf(gettext(" status: One or more devices are "
		    "missing from the system.\n"));
		break;

	case ZPOOL_STATUS_CORRUPT_LABEL_R:
	case ZPOOL_STATUS_CORRUPT_LABEL_NR:
		(void) printf(gettext(" status: One or more devices contains "
		    "corrupted data.\n"));
		break;

	case ZPOOL_STATUS_CORRUPT_DATA:
		(void) printf(
		    gettext(" status: The pool data is corrupted.\n"));
		break;

	case ZPOOL_STATUS_OFFLINE_DEV:
		(void) printf(gettext(" status: One or more devices "
		    "are offlined.\n"));
		break;

	case ZPOOL_STATUS_CORRUPT_POOL:
		(void) printf(gettext(" status: The pool metadata is "
		    "corrupted.\n"));
		break;

	case ZPOOL_STATUS_VERSION_OLDER:
		(void) printf(gettext(" status: The pool is formatted using a "
		    "legacy on-disk version.\n"));
		break;

	case ZPOOL_STATUS_VERSION_NEWER:
		(void) printf(gettext(" status: The pool is formatted using an "
		    "incompatible version.\n"));
		break;

	case ZPOOL_STATUS_FEAT_DISABLED:
		(void) printf(gettext(" status: Some supported features are "
		    "not enabled on the pool.\n"));
		break;

	case ZPOOL_STATUS_UNSUP_FEAT_READ:
		(void) printf(gettext("status: The pool uses the following "
		    "feature(s) not supported on this system:\n"));
		zpool_print_unsup_feat(config);
		break;

	case ZPOOL_STATUS_UNSUP_FEAT_WRITE:
		(void) printf(gettext("status: The pool can only be accessed "
		    "in read-only mode on this system. It\n\tcannot be "
		    "accessed in read-write mode because it uses the "
		    "following\n\tfeature(s) not supported on this system:\n"));
		zpool_print_unsup_feat(config);
		break;

	case ZPOOL_STATUS_HOSTID_MISMATCH:
		(void) printf(gettext(" status: The pool was last accessed by "
		    "another system.\n"));
		break;

	case ZPOOL_STATUS_FAULTED_DEV_R:
	case ZPOOL_STATUS_FAULTED_DEV_NR:
		(void) printf(gettext(" status: One or more devices are "
		    "faulted.\n"));
		break;

	case ZPOOL_STATUS_BAD_LOG:
		(void) printf(gettext(" status: An intent log record cannot be "
		    "read.\n"));
		break;

	case ZPOOL_STATUS_RESILVERING:
		(void) printf(gettext(" status: One or more devices were being "
		    "resilvered.\n"));
		break;

	case ZPOOL_STATUS_NON_NATIVE_ASHIFT:
		(void) printf(gettext("status: One or more devices were "
		    "configured to use a non-native block size.\n"
		    "\tExpect reduced performance.\n"));
		break;

	default:
		/*
		 * No other status can be seen when importing pools.
		 */
		assert(reason == ZPOOL_STATUS_OK);
	}

	/*
	 * Print out an action according to the overall state of the pool.
	 */
	if (vs->vs_state == VDEV_STATE_HEALTHY) {
		if (reason == ZPOOL_STATUS_VERSION_OLDER ||
		    reason == ZPOOL_STATUS_FEAT_DISABLED) {
			(void) printf(gettext(" action: The pool can be "
			    "imported using its name or numeric identifier, "
			    "though\n\tsome features will not be available "
			    "without an explicit 'zpool upgrade'.\n"));
		} else if (reason == ZPOOL_STATUS_HOSTID_MISMATCH) {
			(void) printf(gettext(" action: The pool can be "
			    "imported using its name or numeric "
			    "identifier and\n\tthe '-f' flag.\n"));
		} else {
			(void) printf(gettext(" action: The pool can be "
			    "imported using its name or numeric "
			    "identifier.\n"));
		}
	} else if (vs->vs_state == VDEV_STATE_DEGRADED) {
		(void) printf(gettext(" action: The pool can be imported "
		    "despite missing or damaged devices.  The\n\tfault "
		    "tolerance of the pool may be compromised if imported.\n"));
	} else {
		switch (reason) {
		case ZPOOL_STATUS_VERSION_NEWER:
			(void) printf(gettext(" action: The pool cannot be "
			    "imported.  Access the pool on a system running "
			    "newer\n\tsoftware, or recreate the pool from "
			    "backup.\n"));
			break;
		case ZPOOL_STATUS_UNSUP_FEAT_READ:
			(void) printf(gettext("action: The pool cannot be "
			    "imported. Access the pool on a system that "
			    "supports\n\tthe required feature(s), or recreate "
			    "the pool from backup.\n"));
			break;
		case ZPOOL_STATUS_UNSUP_FEAT_WRITE:
			(void) printf(gettext("action: The pool cannot be "
			    "imported in read-write mode. Import the pool "
			    "with\n"
			    "\t\"-o readonly=on\", access the pool on a system "
			    "that supports the\n\trequired feature(s), or "
			    "recreate the pool from backup.\n"));
			break;
		case ZPOOL_STATUS_MISSING_DEV_R:
		case ZPOOL_STATUS_MISSING_DEV_NR:
		case ZPOOL_STATUS_BAD_GUID_SUM:
			(void) printf(gettext(" action: The pool cannot be "
			    "imported. Attach the missing\n\tdevices and try "
			    "again.\n"));
			break;
		default:
			(void) printf(gettext(" action: The pool cannot be "
			    "imported due to damaged devices or data.\n"));
		}
	}

	/* Print the comment attached to the pool. */
	if (nvlist_lookup_string(config, ZPOOL_CONFIG_COMMENT, &comment) == 0)
		(void) printf(gettext("comment: %s\n"), comment);

	/*
	 * If the state is "closed" or "can't open", and the aux state
	 * is "corrupt data":
	 */
	if (((vs->vs_state == VDEV_STATE_CLOSED) ||
	    (vs->vs_state == VDEV_STATE_CANT_OPEN)) &&
	    (vs->vs_aux == VDEV_AUX_CORRUPT_DATA)) {
		if (pool_state == POOL_STATE_DESTROYED)
			(void) printf(gettext("\tThe pool was destroyed, "
			    "but can be imported using the '-Df' flags.\n"));
		else if (pool_state != POOL_STATE_EXPORTED)
			(void) printf(gettext("\tThe pool may be active on "
			    "another system, but can be imported using\n\t"
			    "the '-f' flag.\n"));
	}

	if (msgid != NULL)
		(void) printf(gettext("   see: http://illumos.org/msg/%s\n"),
		    msgid);

	(void) printf(gettext(" config:\n\n"));

	namewidth = max_width(NULL, nvroot, 0, 0);
	if (namewidth < 10)
		namewidth = 10;

	print_import_config(name, nvroot, namewidth, 0);
	if (num_logs(nvroot) > 0)
		print_logs(NULL, nvroot, namewidth, B_FALSE);

	if (reason == ZPOOL_STATUS_BAD_GUID_SUM) {
		(void) printf(gettext("\n\tAdditional devices are known to "
		    "be part of this pool, though their\n\texact "
		    "configuration cannot be determined.\n"));
	}
}