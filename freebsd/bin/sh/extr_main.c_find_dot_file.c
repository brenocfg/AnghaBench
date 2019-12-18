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
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 char* padvance (char const**,char const**,char*) ; 
 char* pathval () ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  stunalloc (char*) ; 

__attribute__((used)) static char *
find_dot_file(char *basename)
{
	char *fullname;
	const char *opt;
	const char *path = pathval();
	struct stat statb;

	/* don't try this for absolute or relative paths */
	if( strchr(basename, '/'))
		return basename;

	while ((fullname = padvance(&path, &opt, basename)) != NULL) {
		if ((stat(fullname, &statb) == 0) && S_ISREG(statb.st_mode)) {
			/*
			 * Don't bother freeing here, since it will
			 * be freed by the caller.
			 */
			return fullname;
		}
		stunalloc(fullname);
	}
	return basename;
}