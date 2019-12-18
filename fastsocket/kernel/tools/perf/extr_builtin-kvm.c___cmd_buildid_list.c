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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 char** calloc (int,int) ; 
 int cmd_buildid_list (int,char const**,int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
__cmd_buildid_list(const char *file_name, int argc, const char **argv)
{
	int rec_argc, i = 0, j;
	const char **rec_argv;

	rec_argc = argc + 2;
	rec_argv = calloc(rec_argc + 1, sizeof(char *));
	rec_argv[i++] = strdup("buildid-list");
	rec_argv[i++] = strdup("-i");
	rec_argv[i++] = strdup(file_name);
	for (j = 1; j < argc; j++, i++)
		rec_argv[i] = argv[j];

	BUG_ON(i != rec_argc);

	return cmd_buildid_list(i, rec_argv, NULL);
}