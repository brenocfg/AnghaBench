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
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 unsigned long fread (void*,int,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long ftell (int /*<<< orphan*/ *) ; 
 int init_module (void*,unsigned long,char const*) ; 
 void* malloc (unsigned long) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int manual_insmod_26(const char *fname, const char *opts)
{
	unsigned long len, read_len;
	int ret = -1;
	void *buff;
	FILE *f;

	f = fopen(fname, "rb");
	if (f == NULL)
		return -1;

	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);

	buff = malloc(len);
	if (buff == NULL)
		goto fail0;

	read_len = fread(buff, 1, len, f);
	if (read_len != len) {
		fprintf(stderr, "failed to read module\n");
		goto fail1;
	}

	ret = init_module(buff, len, opts);

fail1:
	free(buff);
fail0:
	fclose(f);
	return ret;
}