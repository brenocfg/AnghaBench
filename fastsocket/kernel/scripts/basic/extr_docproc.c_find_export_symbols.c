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
struct symfile {int dummy; } ;
typedef  int /*<<< orphan*/  real_filename ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXLINESZ ; 
 int PATH_MAX ; 
 struct symfile* add_new_file (char*) ; 
 int /*<<< orphan*/  add_new_symbol (struct symfile*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filename_exist (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* srctree ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void find_export_symbols(char * filename)
{
	FILE * fp;
	struct symfile *sym;
	char line[MAXLINESZ];
	if (filename_exist(filename) == NULL) {
		char real_filename[PATH_MAX + 1];
		memset(real_filename, 0, sizeof(real_filename));
		strncat(real_filename, srctree, PATH_MAX);
		strncat(real_filename, "/", PATH_MAX - strlen(real_filename));
		strncat(real_filename, filename,
				PATH_MAX - strlen(real_filename));
		sym = add_new_file(filename);
		fp = fopen(real_filename, "r");
		if (fp == NULL)
		{
			fprintf(stderr, "docproc: ");
			perror(real_filename);
			exit(1);
		}
		while (fgets(line, MAXLINESZ, fp)) {
			char *p;
			char *e;
			if (((p = strstr(line, "EXPORT_SYMBOL_GPL")) != NULL) ||
                            ((p = strstr(line, "EXPORT_SYMBOL")) != NULL)) {
				/* Skip EXPORT_SYMBOL{_GPL} */
				while (isalnum(*p) || *p == '_')
					p++;
				/* Remove parentheses & additional whitespace */
				while (isspace(*p))
					p++;
				if (*p != '(')
					continue; /* Syntax error? */
				else
					p++;
				while (isspace(*p))
					p++;
				e = p;
				while (isalnum(*e) || *e == '_')
					e++;
				*e = '\0';
				add_new_symbol(sym, p);
			}
		}
		fclose(fp);
	}
}