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
typedef  scalar_t__ zpool_prop_t ;
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 scalar_t__ ZPOOL_PROP_CACHEFILE ; 
 scalar_t__ ZPOOL_PROP_INVAL ; 
 scalar_t__ ZPOOL_PROP_VERSION ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,char const*,char*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char const*,char**) ; 
 scalar_t__ prop_list_contains_feature (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 char* zfs_prop_to_name (scalar_t__) ; 
 scalar_t__ zpool_name_to_prop (char const*) ; 
 scalar_t__ zpool_prop_feature (char const*) ; 
 char* zpool_prop_to_name (scalar_t__) ; 

__attribute__((used)) static int
add_prop_list(const char *propname, char *propval, nvlist_t **props,
    boolean_t poolprop)
{
	zpool_prop_t prop = ZPROP_INVAL;
	zfs_prop_t fprop;
	nvlist_t *proplist;
	const char *normnm;
	char *strval;

	if (*props == NULL &&
	    nvlist_alloc(props, NV_UNIQUE_NAME, 0) != 0) {
		(void) fprintf(stderr,
		    gettext("internal error: out of memory\n"));
		return (1);
	}

	proplist = *props;

	if (poolprop) {
		const char *vname = zpool_prop_to_name(ZPOOL_PROP_VERSION);

		if ((prop = zpool_name_to_prop(propname)) == ZPROP_INVAL &&
		    !zpool_prop_feature(propname)) {
			(void) fprintf(stderr, gettext("property '%s' is "
			    "not a valid pool property\n"), propname);
			return (2);
		}

		/*
		 * feature@ properties and version should not be specified
		 * at the same time.
		 */
		if ((prop == ZPOOL_PROP_INVAL && zpool_prop_feature(propname) &&
		    nvlist_exists(proplist, vname)) ||
		    (prop == ZPOOL_PROP_VERSION &&
		    prop_list_contains_feature(proplist))) {
			(void) fprintf(stderr, gettext("'feature@' and "
			    "'version' properties cannot be specified "
			    "together\n"));
			return (2);
		}


		if (zpool_prop_feature(propname))
			normnm = propname;
		else
			normnm = zpool_prop_to_name(prop);
	} else {
		if ((fprop = zfs_name_to_prop(propname)) != ZPROP_INVAL) {
			normnm = zfs_prop_to_name(fprop);
		} else {
			normnm = propname;
		}
	}

	if (nvlist_lookup_string(proplist, normnm, &strval) == 0 &&
	    prop != ZPOOL_PROP_CACHEFILE) {
		(void) fprintf(stderr, gettext("property '%s' "
		    "specified multiple times\n"), propname);
		return (2);
	}

	if (nvlist_add_string(proplist, normnm, propval) != 0) {
		(void) fprintf(stderr, gettext("internal "
		    "error: out of memory\n"));
		return (1);
	}

	return (0);
}