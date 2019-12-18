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
 long ERR ; 
 long current_addr ; 
 char* errmsg ; 
 int /*<<< orphan*/  errno ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 long read_stream (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  scripted ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_escapes (char*) ; 

long
read_file(char *fn, long n)
{
	FILE *fp;
	long size;
	int cs;

	fp = (*fn == '!') ? popen(fn + 1, "r") : fopen(strip_escapes(fn), "r");
	if (fp == NULL) {
		fprintf(stderr, "%s: %s\n", fn, strerror(errno));
		errmsg = "cannot open input file";
		return ERR;
	}
	if ((size = read_stream(fp, n)) < 0) {
		fprintf(stderr, "%s: %s\n", fn, strerror(errno));
		errmsg = "error reading input file";
	}
	if ((cs = (*fn == '!') ?  pclose(fp) : fclose(fp)) < 0) {
		fprintf(stderr, "%s: %s\n", fn, strerror(errno));
		errmsg = "cannot close input file";
	}
	if (size < 0 || cs < 0)
		return ERR;
	if (!scripted)
		fprintf(stdout, "%lu\n", size);
	return current_addr - n;
}