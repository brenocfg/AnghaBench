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
typedef  size_t u_int ;
struct TYPE_2__ {char* path; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* input ; 
 int /*<<< orphan*/  input_new (int /*<<< orphan*/ *,char*,char const*) ; 
 char** paths ; 
 int /*<<< orphan*/  report (char*,char const*) ; 
 int /*<<< orphan*/ * tryopen (char*,char const*) ; 

__attribute__((used)) static void
input_fopen(const char *fname, int loc)
{
	FILE *fp;
	char *path;
	u_int p;

	if (fname[0] == '/') {
		if ((fp = tryopen(NULL, fname)) != NULL) {
			input_new(fp, NULL, fname);
			return;
		}

	} else {
		if (loc) {
			if (input == NULL)
				path = NULL;
			else
				path = input->path;

			if ((fp = tryopen(path, fname)) != NULL) {
				input_new(fp, NULL, fname);
				return;
			}
		}

		for (p = 0; paths[p] != NULL; p++)
			if ((fp = tryopen(paths[p], fname)) != NULL) {
				input_new(fp, paths[p], fname);
				return;
			}
	}
	report("cannot open '%s'", fname);
}