#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  errbuf; TYPE_1__* zhp; } ;
typedef  TYPE_2__ differ_info_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  zfs_hdl; } ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_mounted (int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int zfs_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_mountpoint(differ_info_t *di, char *dsnm, char **mntpt)
{
	boolean_t mounted;

	mounted = is_mounted(di->zhp->zfs_hdl, dsnm, mntpt);
	if (mounted == B_FALSE) {
		(void) snprintf(di->errbuf, sizeof (di->errbuf),
		    dgettext(TEXT_DOMAIN,
		    "Cannot diff an unmounted snapshot"));
		return (zfs_error(di->zhp->zfs_hdl, EZFS_BADTYPE, di->errbuf));
	}

	/* Avoid a double slash at the beginning of root-mounted datasets */
	if (**mntpt == '/' && *(*mntpt + 1) == '\0')
		**mntpt = '\0';
	return (0);
}