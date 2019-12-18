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
struct filter {int dummy; } ;
typedef  int /*<<< orphan*/  regmatch_t ;

/* Variables and functions */
 int MAXLINE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fgets (char*,int const,int /*<<< orphan*/ ) ; 
 scalar_t__ flex_alloc (int const) ; 
 int /*<<< orphan*/  flexerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* headerfilename ; 
 int /*<<< orphan*/  lerrsf (int /*<<< orphan*/ ,char*) ; 
 char* outfilename ; 
 int /*<<< orphan*/  regex_blank_line ; 
 int /*<<< orphan*/  regex_linedir ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* regmatch_dup (int /*<<< orphan*/ *,char*) ; 
 int regmatch_strtol (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int const,char*,int,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 

int filter_fix_linedirs (struct filter *chain)
{
	char   *buf;
	const int readsz = 512;
	int     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	if (!chain)
		return 0;

	buf = (char *) flex_alloc (readsz);
	if (!buf)
		flexerror (_("flex_alloc failed in filter_fix_linedirs"));

	while (fgets (buf, readsz, stdin)) {

		regmatch_t m[10];

		/* Check for #line directive. */
		if (buf[0] == '#'
			&& regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			int     num;
			char   *fname;

			/* extract the line number and filename */
			num = regmatch_strtol (&m[1], buf, NULL, 0);
			fname = regmatch_dup (&m[2], buf);

			if (strcmp (fname,
				outfilename ? outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	headerfilename ? headerfilename : "<stdout>")
					== 0) {

				char    *s1, *s2;
				char	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				while ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					if (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					if (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, "#line %d \"%s\"\n",
					  lineno + 1, filename);
			}
			else {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			free (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		else if (in_gen
			 && regexec (&regex_blank_line, buf, 0, NULL,
				     0) == 0) {
			if (last_was_blank)
				continue;
			else
				last_was_blank = true;
		}

		else {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	if (ferror (stdout))
		lerrsf (_("error writing output file %s"),
			outfilename ? outfilename : "<stdout>");

	else if (fclose (stdout))
		lerrsf (_("error closing output file %s"),
			outfilename ? outfilename : "<stdout>");

	return 0;
}