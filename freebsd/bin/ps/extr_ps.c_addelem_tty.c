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
struct stat {int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ttys; } ;
struct listinfo {scalar_t__ count; scalar_t__ maxcount; TYPE_1__ l; } ;
typedef  int /*<<< orphan*/  pathbuf3 ;
typedef  int /*<<< orphan*/  pathbuf2 ;
typedef  int /*<<< orphan*/  pathbuf ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 char* _PATH_CONSOLE ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 int /*<<< orphan*/  _PATH_PTS ; 
 int /*<<< orphan*/  _PATH_TTY ; 
 int /*<<< orphan*/  expand_list (struct listinfo*) ; 
 int optfatal ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_warn (char*,char const*,...) ; 
 int /*<<< orphan*/  xo_warnx (char*,char const*,...) ; 

__attribute__((used)) static int
addelem_tty(struct listinfo *inf, const char *elem)
{
	const char *ttypath;
	struct stat sb;
	char pathbuf[PATH_MAX], pathbuf2[PATH_MAX], pathbuf3[PATH_MAX];

	ttypath = NULL;
	pathbuf2[0] = '\0';
	pathbuf3[0] = '\0';
	switch (*elem) {
	case '/':
		ttypath = elem;
		break;
	case 'c':
		if (strcmp(elem, "co") == 0) {
			ttypath = _PATH_CONSOLE;
			break;
		}
		/* FALLTHROUGH */
	default:
		strlcpy(pathbuf, _PATH_DEV, sizeof(pathbuf));
		strlcat(pathbuf, elem, sizeof(pathbuf));
		ttypath = pathbuf;
		if (strncmp(pathbuf, _PATH_TTY, strlen(_PATH_TTY)) == 0)
			break;
		if (strncmp(pathbuf, _PATH_PTS, strlen(_PATH_PTS)) == 0)
			break;
		if (strcmp(pathbuf, _PATH_CONSOLE) == 0)
			break;
		/* Check to see if /dev/tty${elem} exists */
		strlcpy(pathbuf2, _PATH_TTY, sizeof(pathbuf2));
		strlcat(pathbuf2, elem, sizeof(pathbuf2));
		if (stat(pathbuf2, &sb) == 0 && S_ISCHR(sb.st_mode)) {
			/* No need to repeat stat() && S_ISCHR() checks */
			ttypath = NULL;
			break;
		}
		/* Check to see if /dev/pts/${elem} exists */
		strlcpy(pathbuf3, _PATH_PTS, sizeof(pathbuf3));
		strlcat(pathbuf3, elem, sizeof(pathbuf3));
		if (stat(pathbuf3, &sb) == 0 && S_ISCHR(sb.st_mode)) {
			/* No need to repeat stat() && S_ISCHR() checks */
			ttypath = NULL;
			break;
		}
		break;
	}
	if (ttypath) {
		if (stat(ttypath, &sb) == -1) {
			if (pathbuf3[0] != '\0')
				xo_warn("%s, %s, and %s", pathbuf3, pathbuf2,
				    ttypath);
			else
				xo_warn("%s", ttypath);
			optfatal = 1;
			return (0);
		}
		if (!S_ISCHR(sb.st_mode)) {
			if (pathbuf3[0] != '\0')
				xo_warnx("%s, %s, and %s: Not a terminal",
				    pathbuf3, pathbuf2, ttypath);
			else
				xo_warnx("%s: Not a terminal", ttypath);
			optfatal = 1;
			return (0);
		}
	}
	if (inf->count >= inf->maxcount)
		expand_list(inf);
	inf->l.ttys[(inf->count)++] = sb.st_rdev;
	return (1);
}