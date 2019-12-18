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
typedef  int /*<<< orphan*/  try ;
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  dirbase ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int cached_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int strlen (char*) ; 

int 
Dir_FindHereOrAbove(char *here, char *search_path, char *result, int rlen) {

	struct stat st;
	char dirbase[MAXPATHLEN + 1], *db_end;
        char try[MAXPATHLEN + 1], *try_end;

	/* copy out our starting point */
	snprintf(dirbase, sizeof(dirbase), "%s", here);
	db_end = dirbase + strlen(dirbase);

	/* loop until we determine a result */
	while (1) {

		/* try and stat(2) it ... */
		snprintf(try, sizeof(try), "%s/%s", dirbase, search_path);
		if (cached_stat(try, &st) != -1) {
			/*
			 * success!  if we found a file, chop off
			 * the filename so we return a directory.
			 */
			if ((st.st_mode & S_IFMT) != S_IFDIR) {
				try_end = try + strlen(try);
				while (try_end > try && *try_end != '/')
					try_end--;
				if (try_end > try) 
					*try_end = 0;	/* chop! */
			}

			/*
			 * done!
			 */
			snprintf(result, rlen, "%s", try);
			return(1);
		}

		/* 
		 * nope, we didn't find it.  if we used up dirbase we've
		 * reached the root and failed.
		 */
		if (db_end == dirbase)
			break;		/* failed! */

		/*
		 * truncate dirbase from the end to move up a dir
		 */
		while (db_end > dirbase && *db_end != '/')
			db_end--;
		*db_end = 0;		/* chop! */

	} /* while (1) */

	/*
	 * we failed... 
	 */
	return(0);
}