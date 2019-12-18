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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ENOTDIR ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/  paxwarn (int,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcspn (char*,char*) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 
 int /*<<< orphan*/  syswarn (int,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
mkpath(char *path)
{
	struct stat sb;
	char *slash;
	int done = 0;

	slash = path;

	while (!done) {
		slash += strspn(slash, "/");
		slash += strcspn(slash, "/");

		done = (*slash == '\0');
		*slash = '\0';

		if (stat(path, &sb)) {
			if (errno != ENOENT || mkdir(path, 0777)) {
				paxwarn(1, "%s", path);
				return (-1);
			}
		} else if (!S_ISDIR(sb.st_mode)) {
			syswarn(1, ENOTDIR, "%s", path);
			return (-1);
		}

		if (!done)
			*slash = '/';
	}

	return (0);
}