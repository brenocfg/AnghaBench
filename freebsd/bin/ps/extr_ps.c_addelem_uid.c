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
typedef  int /*<<< orphan*/  uid_t ;
typedef  scalar_t__ u_long ;
struct passwd {int /*<<< orphan*/  pw_uid; } ;
struct TYPE_2__ {int /*<<< orphan*/ * uids; } ;
struct listinfo {scalar_t__ count; scalar_t__ maxcount; TYPE_1__ l; int /*<<< orphan*/  lname; } ;

/* Variables and functions */
 scalar_t__ MAXLOGNAME ; 
 scalar_t__ UID_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  expand_list (struct listinfo*) ; 
 struct passwd* getpwnam (char const*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int optfatal ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  xo_warnx (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
addelem_uid(struct listinfo *inf, const char *elem)
{
	struct passwd *pwd;
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

	pwd = getpwnam(elem);
	if (pwd == NULL) {
		errno = 0;
		bigtemp = strtoul(elem, &endp, 10);
		if (errno != 0 || *endp != '\0' || bigtemp > UID_MAX)
			xo_warnx("No %s named '%s'", inf->lname, elem);
		else {
			/* The string is all digits, so it might be a userID. */
			pwd = getpwuid((uid_t)bigtemp);
			if (pwd == NULL)
				xo_warnx("No %s name or ID matches '%s'",
				    inf->lname, elem);
		}
	}
	if (pwd == NULL) {
		/*
		 * These used to be treated as minor warnings (and the
		 * option was simply ignored), but now they are fatal
		 * errors (and the command will be aborted).
		 */
		optfatal = 1;
		return (0);
	}
	if (inf->count >= inf->maxcount)
		expand_list(inf);
	inf->l.uids[(inf->count)++] = pwd->pw_uid;
	return (1);
}