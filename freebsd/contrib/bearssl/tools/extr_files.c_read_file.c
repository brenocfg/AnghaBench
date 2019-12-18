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
typedef  int /*<<< orphan*/  bvector ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_ADDMANY (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  VEC_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_INIT ; 
 size_t VEC_LEN (int /*<<< orphan*/ ) ; 
 unsigned char* VEC_TOARRAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 size_t fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

unsigned char *
read_file(const char *fname, size_t *len)
{
	bvector vbuf = VEC_INIT;
	FILE *f;

	*len = 0;
	f = fopen(fname, "rb");
	if (f == NULL) {
		fprintf(stderr,
			"ERROR: could not open file '%s' for reading\n", fname);
		return NULL;
	}
	for (;;) {
		unsigned char tmp[1024];
		size_t rlen;

		rlen = fread(tmp, 1, sizeof tmp, f);
		if (rlen == 0) {
			unsigned char *buf;

			if (ferror(f)) {
				fprintf(stderr,
					"ERROR: read error on file '%s'\n",
					fname);
				fclose(f);
				return NULL;
			}
			buf = VEC_TOARRAY(vbuf);
			*len = VEC_LEN(vbuf);
			VEC_CLEAR(vbuf);
			fclose(f);
			return buf;
		}
		VEC_ADDMANY(vbuf, tmp, rlen);
	}
}