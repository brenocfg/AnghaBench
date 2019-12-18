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
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  SET_BINARY (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_version (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 

int
main (int argc, char *argv[])
{
  int c;
  int i;

#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
#if defined (HAVE_SETLOCALE)
  setlocale (LC_CTYPE, "");
#endif
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  if (argc != 1)
    {
      int ishelp = 0;
      int isvers = 0;
      FILE *stream;

      if (argc == 2 && argv[1][0] == '-')
	{
	  const char *opt = &argv[1][1];
	  if (*opt == '-')
	    ++opt;
	  ishelp = *opt == 'h' || *opt == 'H';
	  isvers = *opt == 'v' || *opt == 'V';
	}

      if (isvers)
	print_version ("bin2c");

      stream = ishelp ? stdout : stderr;
      fprintf (stream, _("Usage: %s < input_file > output_file\n"), argv[0]);
      fprintf (stream, _("Prints bytes from stdin in hex format.\n"));
      exit (!ishelp);
    }

  SET_BINARY (fileno (stdin));

  i = 0;
  while ((c = getc (stdin)) != EOF)
    {
      printf ("0x%02x,", c);
      if (++i == 16)
	{
	  printf ("\n");
	  i = 0;
	}
    }
  if (i != 0)
    printf ("\n");

  exit (0);
}