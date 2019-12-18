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
typedef  int /*<<< orphan*/ * gzFile ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int UNCOMPRESS_BUFFER_SIZE ; 
 void* Util_malloc (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fwrite (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gzopen (char const*,char*) ; 
 int gzread (int /*<<< orphan*/ *,void*,int) ; 

int CompFile_ExtractGZ(const char *infilename, FILE *outfp)
{
#ifndef HAVE_LIBZ
	Log_print("This executable cannot decompress ZLIB files");
	return FALSE;
#else
	/* TODO: replace gz* with low-level light-weight ZLIB functions. */
	gzFile gzf = gzopen(infilename, "rb");
	void *buf;
	int result;
	if (gzf == NULL) {
		Log_print("ZLIB could not open file %s", infilename);
		return FALSE;
	}
#define UNCOMPRESS_BUFFER_SIZE 32768
	buf = Util_malloc(UNCOMPRESS_BUFFER_SIZE);
	do {
		result = gzread(gzf, buf, UNCOMPRESS_BUFFER_SIZE);
		if (result > 0) {
			if ((int) fwrite(buf, 1, result, outfp) != result)
				result = -1;
		}
	} while (result == UNCOMPRESS_BUFFER_SIZE);
	free(buf);
	gzclose(gzf);
	return result >= 0;
#endif	/* HAVE_LIBZ */
}