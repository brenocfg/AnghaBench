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
struct stat {scalar_t__ st_mtime; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int try_ropen_file(const char *fname, int *time)
{
	struct stat st;
	FILE *f;

	f = fopen(fname, "rb");
	if (f) {
		if (time != NULL) {
			*time = 0;
			if (fstat(fileno(f), &st) == 0)
				*time = (int)st.st_mtime;
		}
		fclose(f);
		return 1;
	}
	return 0;
}