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
struct stat {int st_flags; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int EOF ; 
 int SF_APPEND ; 
 int SF_IMMUTABLE ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int UF_APPEND ; 
 int UF_IMMUTABLE ; 
 int /*<<< orphan*/  W_OK ; 
 int /*<<< orphan*/  access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char* fflagstostr (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getchar () ; 
 char* group_from_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin_ok ; 
 int /*<<< orphan*/  strmode (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uid ; 
 char* user_from_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check(const char *path, const char *name, struct stat *sp)
{
	int ch, first;
	char modep[15], *flagsp;

	/* Check -i first. */
	if (iflag)
		(void)fprintf(stderr, "remove %s? ", path);
	else {
		/*
		 * If it's not a symbolic link and it's unwritable and we're
		 * talking to a terminal, ask.  Symbolic links are excluded
		 * because their permissions are meaningless.  Check stdin_ok
		 * first because we may not have stat'ed the file.
		 */
		if (!stdin_ok || S_ISLNK(sp->st_mode) ||
		    (!access(name, W_OK) &&
		    !(sp->st_flags & (SF_APPEND|SF_IMMUTABLE)) &&
		    (!(sp->st_flags & (UF_APPEND|UF_IMMUTABLE)) || !uid)))
			return (1);
		strmode(sp->st_mode, modep);
		if ((flagsp = fflagstostr(sp->st_flags)) == NULL)
			err(1, "fflagstostr");
		(void)fprintf(stderr, "override %s%s%s/%s %s%sfor %s? ",
		    modep + 1, modep[10] == ' ' ? "" : " ",
		    user_from_uid(sp->st_uid, 0),
		    group_from_gid(sp->st_gid, 0),
		    *flagsp ? flagsp : "", *flagsp ? " " : "",
		    path);
		free(flagsp);
	}
	(void)fflush(stderr);

	first = ch = getchar();
	while (ch != '\n' && ch != EOF)
		ch = getchar();
	return (first == 'y' || first == 'Y');
}