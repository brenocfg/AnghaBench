#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct holdarg {char const* snapname; char const* tag; int /*<<< orphan*/  nvl; int /*<<< orphan*/  recursive; } ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  zfs_handle_dup (TYPE_1__*) ; 
 int zfs_hold_nvl (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_hold_one (int /*<<< orphan*/ ,struct holdarg*) ; 
 int /*<<< orphan*/  zfs_standard_error (int /*<<< orphan*/ ,int,char*) ; 

int
zfs_hold(zfs_handle_t *zhp, const char *snapname, const char *tag,
    boolean_t recursive, int cleanup_fd)
{
	int ret;
	struct holdarg ha;

	ha.nvl = fnvlist_alloc();
	ha.snapname = snapname;
	ha.tag = tag;
	ha.recursive = recursive;
	(void) zfs_hold_one(zfs_handle_dup(zhp), &ha);

	if (nvlist_empty(ha.nvl)) {
		char errbuf[1024];

		fnvlist_free(ha.nvl);
		ret = ENOENT;
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN,
		    "cannot hold snapshot '%s@%s'"),
		    zhp->zfs_name, snapname);
		(void) zfs_standard_error(zhp->zfs_hdl, ret, errbuf);
		return (ret);
	}

	ret = zfs_hold_nvl(zhp, cleanup_fd, ha.nvl);
	fnvlist_free(ha.nvl);

	return (ret);
}