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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPA_VERSION_FEATURES ; 
 int SPA_VERSION_IS_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VERSION ; 
 int /*<<< orphan*/  assert (int) ; 
 char* gettext (char*) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 int zpool_upgrade (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
upgrade_version(zpool_handle_t *zhp, uint64_t version)
{
	int ret;
	nvlist_t *config;
	uint64_t oldversion;

	config = zpool_get_config(zhp, NULL);
	verify(nvlist_lookup_uint64(config, ZPOOL_CONFIG_VERSION,
	    &oldversion) == 0);

	assert(SPA_VERSION_IS_SUPPORTED(oldversion));
	assert(oldversion < version);

	ret = zpool_upgrade(zhp, version);
	if (ret != 0)
		return (ret);

	if (version >= SPA_VERSION_FEATURES) {
		(void) printf(gettext("Successfully upgraded "
		    "'%s' from version %llu to feature flags.\n"),
		    zpool_get_name(zhp), oldversion);
	} else {
		(void) printf(gettext("Successfully upgraded "
		    "'%s' from version %llu to version %llu.\n"),
		    zpool_get_name(zhp), oldversion, version);
	}

	return (0);
}