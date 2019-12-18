#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sc_prop; scalar_t__ sc_reverse; struct TYPE_4__* sc_next; } ;
typedef  TYPE_1__ zfs_sort_column_t ;
typedef  int zfs_prop_t ;
struct TYPE_5__ {scalar_t__ si_numname; TYPE_1__* si_sortcol; } ;
typedef  TYPE_2__ us_sort_info_t ;
struct TYPE_6__ {int /*<<< orphan*/ * usn_nvl; } ;
typedef  TYPE_3__ us_node_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
#define  ZFS_PROP_NAME 131 
#define  ZFS_PROP_QUOTA 130 
#define  ZFS_PROP_TYPE 129 
#define  ZFS_PROP_USED 128 
 scalar_t__ nvlist_lookup_boolean_value (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,char const*,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint32 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int strcmp (char*,char*) ; 
 int /*<<< orphan*/  us_populated ; 

__attribute__((used)) static int
us_compare(const void *larg, const void *rarg, void *unused)
{
	const us_node_t *l = larg;
	const us_node_t *r = rarg;
	us_sort_info_t *si = (us_sort_info_t *)unused;
	zfs_sort_column_t *sortcol = si->si_sortcol;
	boolean_t numname = si->si_numname;
	nvlist_t *lnvl = l->usn_nvl;
	nvlist_t *rnvl = r->usn_nvl;
	int rc = 0;
	boolean_t lvb, rvb;

	for (; sortcol != NULL; sortcol = sortcol->sc_next) {
		char *lvstr = "";
		char *rvstr = "";
		uint32_t lv32 = 0;
		uint32_t rv32 = 0;
		uint64_t lv64 = 0;
		uint64_t rv64 = 0;
		zfs_prop_t prop = sortcol->sc_prop;
		const char *propname = NULL;
		boolean_t reverse = sortcol->sc_reverse;

		switch (prop) {
		case ZFS_PROP_TYPE:
			propname = "type";
			(void) nvlist_lookup_uint32(lnvl, propname, &lv32);
			(void) nvlist_lookup_uint32(rnvl, propname, &rv32);
			if (rv32 != lv32)
				rc = (rv32 < lv32) ? 1 : -1;
			break;
		case ZFS_PROP_NAME:
			propname = "name";
			if (numname) {
compare_nums:
				(void) nvlist_lookup_uint64(lnvl, propname,
				    &lv64);
				(void) nvlist_lookup_uint64(rnvl, propname,
				    &rv64);
				if (rv64 != lv64)
					rc = (rv64 < lv64) ? 1 : -1;
			} else {
				if ((nvlist_lookup_string(lnvl, propname,
						&lvstr) == ENOENT) ||
				    (nvlist_lookup_string(rnvl, propname,
						&rvstr) == ENOENT)) {
					goto compare_nums;
				}
				rc = strcmp(lvstr, rvstr);
			}
			break;
		case ZFS_PROP_USED:
		case ZFS_PROP_QUOTA:
			if (!us_populated)
				break;
			if (prop == ZFS_PROP_USED)
				propname = "used";
			else
				propname = "quota";
			(void) nvlist_lookup_uint64(lnvl, propname, &lv64);
			(void) nvlist_lookup_uint64(rnvl, propname, &rv64);
			if (rv64 != lv64)
				rc = (rv64 < lv64) ? 1 : -1;
			break;

		default:
			break;
		}

		if (rc != 0) {
			if (rc < 0)
				return (reverse ? 1 : -1);
			else
				return (reverse ? -1 : 1);
		}
	}

	/*
	 * If entries still seem to be the same, check if they are of the same
	 * type (smbentity is added only if we are doing SID to POSIX ID
	 * translation where we can have duplicate type/name combinations).
	 */
	if (nvlist_lookup_boolean_value(lnvl, "smbentity", &lvb) == 0 &&
	    nvlist_lookup_boolean_value(rnvl, "smbentity", &rvb) == 0 &&
	    lvb != rvb)
		return (lvb < rvb ? -1 : 1);

	return (0);
}