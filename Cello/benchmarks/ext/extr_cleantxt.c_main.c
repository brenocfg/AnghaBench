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
 int EOF ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 scalar_t__ isgraph (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char *argv[])
{
	FILE *fp;
	int c = EOF;
	if (argc == 1) {
		fprintf(stderr, "Usage: cleantxt <file>\n");
		return 1;
	}
	fp = strcmp(argv[1], "-")? fopen(argv[1], "rb") : stdin;
	if (fp == 0) {
		fprintf(stderr, "ERROR: fail to open the input file.\n");
		return 1;
	}
	while (!feof(fp)) {
		c = fgetc(fp);
		if (isgraph(c) || c == '\t' || c == '\n' || c == ' ')
			fputc(c, stdout);
	}
	if (c != '\n') fputc('\n', stdout);
	fclose(fp);
	return 0;
}