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
typedef  scalar_t__ u_long ;
struct TYPE_2__ {int /*<<< orphan*/ * gids; } ;
struct listinfo {scalar_t__ count; scalar_t__ maxcount; TYPE_1__ l; int /*<<< orphan*/  lname; } ;
struct group {int /*<<< orphan*/  gr_gid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 scalar_t__ GID_MAX ; 
 scalar_t__ MAXLOGNAME ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  expand_list (struct listinfo*) ; 
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 struct group* getgrnam (char const*) ; 
 int optfatal ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  xo_warnx (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
addelem_gid(struct listinfo *inf, const char *elem)
{
	struct group *grp;
	const char *nameorID;
	char *endp;
	u_long bigtemp;

	if (*elem == '\0' || strlen(elem) >= MAXLOGNAME) {
		if (*elem == '\0')
			xo_warnx("Invalid (zero-length) %s name", inf->lname);
		else
			xo_warnx("%s name too long: %s", inf->lname, elem);
		optfatal = 1;
		return (0);		/* Do not add this value. */
	}

	/*
	 * SUSv3 states that `ps -G grouplist' should match "real-group
	 * ID numbers", and does not mention group-names.  I do want to
	 * also support group-names, so this tries for a group-id first,
	 * and only tries for a name if that doesn't work.  This is the
	 * opposite order of what is done in addelem_uid(), but in
	 * practice the order would only matter for group-names which
	 * are all-numeric.
	 */
	grp = NULL;
	nameorID = "named";
	errno = 0;
	bigtemp = strtoul(elem, &endp, 10);
	if (errno == 0 && *endp == '\0' && bigtemp <= GID_MAX) {
		nameorID = "name or ID matches";
		grp = getgrgid((gid_t)bigtemp);
	}
	if (grp == NULL)
		grp = getgrnam(elem);
	if (grp == NULL) {
		xo_warnx("No %s %s '%s'", inf->lname, nameorID, elem);
		optfatal = 1;
		return (0);
	}
	if (inf->count >= inf->maxcount)
		expand_list(inf);
	inf->l.gids[(inf->count)++] = grp->gr_gid;
	return (1);
}