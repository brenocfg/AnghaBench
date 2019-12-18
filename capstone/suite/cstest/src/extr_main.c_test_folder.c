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
 int /*<<< orphan*/  get_filename_ext (char*) ; 
 int /*<<< orphan*/  listdir (char const*,char***,int*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_file (char*) ; 

__attribute__((used)) static void test_folder(const char *folder)
{
	char **files;
	int num_files, i;

	files = NULL;
	num_files = 0;
	listdir(folder, &files, &num_files);
	for (i = 0; i < num_files; ++i) {
		if (strcmp("cs", get_filename_ext(files[i])))
			continue;
		test_file(files[i]);
	}
}