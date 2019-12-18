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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ POOL_STATE_EXPORTED ; 
 scalar_t__ POOL_STATE_UNAVAIL ; 
 int /*<<< orphan*/  SPA_VERSION_IS_SUPPORTED (scalar_t__) ; 
 int ZFS_IMPORT_ANY_HOST ; 
 int ZFS_IMPORT_ONLY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_HOSTID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_HOSTNAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_STATE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TIMESTAMP ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VERSION ; 
 int /*<<< orphan*/  asctime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 unsigned long gethostid () ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  localtime (scalar_t__*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_enable_datasets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_get_state (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_import_props (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zpool_open_canfail (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
do_import(nvlist_t *config, const char *newname, const char *mntopts,
    nvlist_t *props, int flags)
{
	zpool_handle_t *zhp;
	char *name;
	uint64_t state;
	uint64_t version;

	verify(nvlist_lookup_string(config, ZPOOL_CONFIG_POOL_NAME,
	    &name) == 0);

	verify(nvlist_lookup_uint64(config,
	    ZPOOL_CONFIG_POOL_STATE, &state) == 0);
	verify(nvlist_lookup_uint64(config,
	    ZPOOL_CONFIG_VERSION, &version) == 0);
	if (!SPA_VERSION_IS_SUPPORTED(version)) {
		(void) fprintf(stderr, gettext("cannot import '%s': pool "
		    "is formatted using an unsupported ZFS version\n"), name);
		return (1);
	} else if (state != POOL_STATE_EXPORTED &&
	    !(flags & ZFS_IMPORT_ANY_HOST)) {
		uint64_t hostid;

		if (nvlist_lookup_uint64(config, ZPOOL_CONFIG_HOSTID,
		    &hostid) == 0) {
			if ((unsigned long)hostid != gethostid()) {
				char *hostname;
				uint64_t timestamp;
				time_t t;

				verify(nvlist_lookup_string(config,
				    ZPOOL_CONFIG_HOSTNAME, &hostname) == 0);
				verify(nvlist_lookup_uint64(config,
				    ZPOOL_CONFIG_TIMESTAMP, &timestamp) == 0);
				t = timestamp;
				(void) fprintf(stderr, gettext("cannot import "
				    "'%s': pool may be in use from other "
				    "system, it was last accessed by %s "
				    "(hostid: 0x%lx) on %s"), name, hostname,
				    (unsigned long)hostid,
				    asctime(localtime(&t)));
				(void) fprintf(stderr, gettext("use '-f' to "
				    "import anyway\n"));
				return (1);
			}
		} else {
			(void) fprintf(stderr, gettext("cannot import '%s': "
			    "pool may be in use from other system\n"), name);
			(void) fprintf(stderr, gettext("use '-f' to import "
			    "anyway\n"));
			return (1);
		}
	}

	if (zpool_import_props(g_zfs, config, newname, props, flags) != 0)
		return (1);

	if (newname != NULL)
		name = (char *)newname;

	if ((zhp = zpool_open_canfail(g_zfs, name)) == NULL)
		return (1);

	if (zpool_get_state(zhp) != POOL_STATE_UNAVAIL &&
	    !(flags & ZFS_IMPORT_ONLY) &&
	    zpool_enable_datasets(zhp, mntopts, 0) != 0) {
		zpool_close(zhp);
		return (1);
	}

	zpool_close(zhp);
	return (0);
}