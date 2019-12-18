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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int DUMP_FIRST ; 
 int DUMP_LAST ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int NO_DUMP ; 
 int /*<<< orphan*/  PRINT_PERR (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int sscanf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int get_dump_num(const char *dumpdir, int mode)
{
	DIR *dir = NULL;
	struct dirent *dir_ent;
	int dump_found, rc;

	rc = 0;
	dump_found = 0;
	dir = opendir(dumpdir);
	if (!dir) {
		PRINT_PERR("Cannot evalute dump number\n");
		return -2;
	}

	while ((dir_ent = readdir(dir))) {
		int num;
		if (sscanf(dir_ent->d_name, "dump.%ui", &num) == 1) {
			char suffix[1024] = {};

			/*
			 * check if we have something like dump.001
			 * this is not treated as dump, since we do not allow
			 * leading zeros.
			 * Also files like dump.-1, dump.-10 are ignored.
			 */
			sscanf(dir_ent->d_name, "dump.%s", suffix);
			if (suffix[0] == '-')
				continue;
			if ((suffix[0] == '0') && isdigit(suffix[1]))
				continue;
			if (!dump_found) {
				dump_found = 1;
				rc = num;
			} else if (mode == DUMP_LAST) {
				rc = MAX(num, rc);
			} else if (mode == DUMP_FIRST) {
				rc = MIN(num, rc);
			}
		}
	}
	if (!dump_found)
		rc = NO_DUMP;
	closedir(dir);

	return rc;
}