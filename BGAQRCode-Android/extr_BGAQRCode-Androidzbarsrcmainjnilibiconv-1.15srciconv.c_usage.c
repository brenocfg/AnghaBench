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

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void usage (int exitcode)
{
  if (exitcode != 0) {
    const char* helpstring1 =
      /* TRANSLATORS: The first line of the short usage message.  */
      _("Usage: iconv [-c] [-s] [-f fromcode] [-t tocode] [file ...]");
    const char* helpstring2 =
      /* TRANSLATORS: The second line of the short usage message.
         Align it correctly against the first line.  */
      _("or:    iconv -l");
    fprintf(stderr, "%s\n%s\n", helpstring1, helpstring2);
    fprintf(stderr, _("Try '%s --help' for more information.\n"), program_name);
  } else {
    /* xgettext: no-wrap */
    /* TRANSLATORS: The first line of the long usage message.
       The %s placeholder expands to the program name.  */
    printf(_("\
Usage: %s [OPTION...] [-f ENCODING] [-t ENCODING] [INPUTFILE...]\n"),
           program_name);
    /* xgettext: no-wrap */
    /* TRANSLATORS: The second line of the long usage message.
       Align it correctly against the first line.
       The %s placeholder expands to the program name.  */
    printf(_("\
or:    %s -l\n"),
           program_name);
    printf("\n");
    /* xgettext: no-wrap */
    /* TRANSLATORS: Description of the iconv program.  */
    printf(_("\
Converts text from one encoding to another encoding.\n"));
    printf("\n");
    /* xgettext: no-wrap */
    printf(_("\
Options controlling the input and output format:\n"));
    /* xgettext: no-wrap */
    printf(_("\
  -f ENCODING, --from-code=ENCODING\n\
                              the encoding of the input\n"));
    /* xgettext: no-wrap */
    printf(_("\
  -t ENCODING, --to-code=ENCODING\n\
                              the encoding of the output\n"));
    printf("\n");
    /* xgettext: no-wrap */
    printf(_("\
Options controlling conversion problems:\n"));
    /* xgettext: no-wrap */
    printf(_("\
  -c                          discard unconvertible characters\n"));
    /* xgettext: no-wrap */
    printf(_("\
  --unicode-subst=FORMATSTRING\n\
                              substitution for unconvertible Unicode characters\n"));
    /* xgettext: no-wrap */
    printf(_("\
  --byte-subst=FORMATSTRING   substitution for unconvertible bytes\n"));
    /* xgettext: no-wrap */
    printf(_("\
  --widechar-subst=FORMATSTRING\n\
                              substitution for unconvertible wide characters\n"));
    printf("\n");
    /* xgettext: no-wrap */
    printf(_("\
Options controlling error output:\n"));
    /* xgettext: no-wrap */
    printf(_("\
  -s, --silent                suppress error messages about conversion problems\n"));
    printf("\n");
    /* xgettext: no-wrap */
    printf(_("\
Informative output:\n"));
    /* xgettext: no-wrap */
    printf(_("\
  -l, --list                  list the supported encodings\n"));
    /* xgettext: no-wrap */
    printf(_("\
  --help                      display this help and exit\n"));
    /* xgettext: no-wrap */
    printf(_("\
  --version                   output version information and exit\n"));
    printf("\n");
    /* TRANSLATORS: The placeholder indicates the bug-reporting address
       for this package.  Please add _another line_ saying
       "Report translation bugs to <...>\n" with the address for translation
       bugs (typically your translation team's web or email address).  */
    fputs(_("Report bugs to <bug-gnu-libiconv@gnu.org>.\n"),stdout);
  }
  exit(exitcode);
}