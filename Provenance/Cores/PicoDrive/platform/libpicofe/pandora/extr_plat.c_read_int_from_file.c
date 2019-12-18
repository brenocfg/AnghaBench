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
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fscanf (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static int read_int_from_file(const char *fname)
{
	int ret = -1;
	FILE *f;

	f = fopen(fname, "r");
	if (f) {
		fscanf(f, "%d", &ret);
		fclose(f);
	}
	return ret;
}