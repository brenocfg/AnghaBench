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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ mkdir (char*,int /*<<< orphan*/ ) ; 
 char* simplify (char const*) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 

int
mkdirp(const char *d, mode_t mode)
{
	char  *endptr, *ptr, *slash, *str;

	str = simplify(d);

	/* If space couldn't be allocated for the simplified names, return. */

	if (str == NULL)
		return (-1);

		/* Try to make the directory */

	if (mkdir(str, mode) == 0) {
		free(str);
		return (0);
	}
	if (errno != ENOENT) {
		free(str);
		return (-1);
	}
	endptr = strrchr(str, '\0');
	slash = strrchr(str, '/');

		/* Search upward for the non-existing parent */

	while (slash != NULL) {

		ptr = slash;
		*ptr = '\0';

			/* If reached an existing parent, break */

		if (access(str, F_OK) == 0)
			break;

			/* If non-existing parent */

		else {
			slash = strrchr(str, '/');

				/* If under / or current directory, make it. */

			if (slash == NULL || slash == str) {
				if (mkdir(str, mode) != 0 && errno != EEXIST) {
					free(str);
					return (-1);
				}
				break;
			}
		}
	}

	/* Create directories starting from upmost non-existing parent */

	while ((ptr = strchr(str, '\0')) != endptr) {
		*ptr = '/';
		if (mkdir(str, mode) != 0 && errno != EEXIST) {
			/*
			 *  If the mkdir fails because str already
			 *  exists (EEXIST), then str has the form
			 *  "existing-dir/..", and this is really
			 *  ok. (Remember, this loop is creating the
			 *  portion of the path that didn't exist)
			 */
			free(str);
			return (-1);
		}
	}
	free(str);
	return (0);
}