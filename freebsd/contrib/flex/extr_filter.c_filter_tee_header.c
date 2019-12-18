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
struct filter {int /*<<< orphan*/ * extra; int /*<<< orphan*/  next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char* check_4_gnu_m4 ; 
 int dup (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_apply_chain (int /*<<< orphan*/ ) ; 
 scalar_t__ flex_alloc (int const) ; 
 int /*<<< orphan*/  flexerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flexfatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ *) ; 
 char* headerfilename ; 
 int /*<<< orphan*/  lerrsf (int /*<<< orphan*/ ,char*) ; 
 char* outfilename ; 
 char* prefix ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ wait (int /*<<< orphan*/ ) ; 

int filter_tee_header (struct filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	const int readsz = 512;
	char   *buf;
	int     to_cfd = -1;
	FILE   *to_c = NULL, *to_h = NULL;
	bool    write_header;

	write_header = (chain->extra != NULL);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	if ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	if (write_header) {
		if (freopen ((char *) chain->extra, "w", stdout) == NULL)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	if (write_header) {
        fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
		fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
	    fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define( [[M4_YY_IN_HEADER]],[[]])m4_dnl\n",
		       to_h);
		fprintf (to_h, "#ifndef %sHEADER_H\n", prefix);
		fprintf (to_h, "#define %sHEADER_H 1\n", prefix);
		fprintf (to_h, "#define %sIN_HEADER 1\n\n", prefix);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 headerfilename ? headerfilename : "<stdout>");

	}

    fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 outfilename ? outfilename : "<stdout>");

	buf = (char *) flex_alloc (readsz);
	if (!buf)
		flexerror (_("flex_alloc failed in filter_tee_header"));
	while (fgets (buf, readsz, stdin)) {
		fputs (buf, to_c);
		if (write_header)
			fputs (buf, to_h);
	}

	if (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		fprintf (to_h, "#line 4000 \"M4_YY_OUTFILE_NAME\"\n");

		fprintf (to_h, "#undef %sIN_HEADER\n", prefix);
		fprintf (to_h, "#endif /* %sHEADER_H */\n", prefix);
		fputs ("m4_undefine( [[M4_YY_IN_HEADER]])m4_dnl\n", to_h);

		fflush (to_h);
		if (ferror (to_h))
			lerrsf (_("error writing output file %s"),
				(char *) chain->extra);

		else if (fclose (to_h))
			lerrsf (_("error closing output file %s"),
				(char *) chain->extra);
	}

	fflush (to_c);
	if (ferror (to_c))
		lerrsf (_("error writing output file %s"),
			outfilename ? outfilename : "<stdout>");

	else if (fclose (to_c))
		lerrsf (_("error closing output file %s"),
			outfilename ? outfilename : "<stdout>");

	while (wait (0) > 0) ;

	exit (0);
	return 0;
}