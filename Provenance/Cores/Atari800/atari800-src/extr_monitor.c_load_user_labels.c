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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  UWORD ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Util_chomp (char*) ; 
 int /*<<< orphan*/  add_user_label (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free_user_labels () ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int symtable_user_size ; 

__attribute__((used)) static void load_user_labels(const char *filename)
{
	FILE *fp;
	char line[256];
	if (filename == NULL) {
		printf("You must specify a filename\n");
		return;
	}
	/* "rb" and not "r", because we strip EOLs ourselves
	   - this is better, because we can use CR/LF files on Unix */
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		perror(filename);
		return;
	}
	free_user_labels();
	while (fgets(line, sizeof(line), fp)) {
		char *p;
		unsigned int value = 0;
		int digits = 0;
		/* Find first 4 hex digits or more. */
		/* We don't support "Cafe Assembler", "Dead Assembler" or "C0de Assembler". ;-) */
		for (p = line; *p != '\0'; p++) {
			if (*p >= '0' && *p <= '9') {
				value = (value << 4) + *p - '0';
				digits++;
			}
			else if (*p >= 'A' && *p <= 'F') {
				value = (value << 4) + *p - 'A' + 10;
				digits++;
			}
			else if (*p >= 'a' && *p <= 'f') {
				value = (value << 4) + *p - 'a' + 10;
				digits++;
			}
			else if (digits >= 4)
				break;
			else if (*p == '-')
				break; /* ignore labels with negative values */
			else {
				/* note that xasm can put "2" before the label value and mads puts "00" */
				value = 0;
				digits = 0;
			}
		}
		if (*p != ' ' && *p != '\t')
			continue;
		if (value > 0xffff || digits > 8)
			continue;
		do
			p++;
		while (*p == ' ' || *p == '\t');
		Util_chomp(p);
		if (*p == '\0')
			continue;
		add_user_label(p, (UWORD) value);
	}
	fclose(fp);
	printf("Loaded %d labels\n", symtable_user_size);
}