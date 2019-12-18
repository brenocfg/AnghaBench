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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int is_good_path(char *path)
{
	int len = strlen(path);

	path[len-2] = 'n';
	path[len-1] = 'o';

	FILE *f = fopen(path, "rb");

	path[len-2] = 'd';
	path[len-1] = 'a';

	if (f) {
		fclose(f);
		return 1;
	}
	printf("not good path: %s\n", path);
	return 0;
}