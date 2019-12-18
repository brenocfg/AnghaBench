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
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 size_t fwrite (unsigned char const*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int
write_file(const char *fname, const void *data, size_t len)
{
	FILE *f;
	const unsigned char *buf;

	f = fopen(fname, "wb");
	if (f == NULL) {
		fprintf(stderr,
			"ERROR: could not open file '%s' for reading\n", fname);
		return -1;
	}
	buf = data;
	while (len > 0) {
		size_t wlen;

		wlen = fwrite(buf, 1, len, f);
		if (wlen == 0) {
			fprintf(stderr,
				"ERROR: could not write all bytes to '%s'\n",
				fname);
			fclose(f);
			return -1;
		}
		buf += wlen;
		len -= wlen;
	}
	if (ferror(f)) {
		fprintf(stderr, "ERROR: write error on file '%s'\n", fname);
		fclose(f);
		return -1;
	}
	fclose(f);
	return 0;
}