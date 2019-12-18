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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 size_t fwrite (void const*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
write_to_file(const char *name, const void *data, size_t len)
{
	FILE *f;

	f = fopen(name, "wb");
	if (f == NULL) {
		fprintf(stderr,
			"ERROR: cannot open file '%s' for writing\n",
			name);
		return 0;
	}
	if (fwrite(data, 1, len, f) != len) {
		fclose(f);
		fprintf(stderr,
			"ERROR: cannot write to file '%s'\n",
			name);
		return 0;
	}
	fclose(f);
	return 1;
}