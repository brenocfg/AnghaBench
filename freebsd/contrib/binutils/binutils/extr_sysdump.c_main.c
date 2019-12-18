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
struct option {char* member_0; char member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  const member_1; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FOPEN_RB ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  file ; 
 int /*<<< orphan*/  fopen (char*,int /*<<< orphan*/ ) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  module () ; 
#define  no_argument 128 
 int optind ; 
 int /*<<< orphan*/  print_version (char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_usage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 

int
main (int ac, char **av)
{
  char *input_file = NULL;
  int opt;
  static struct option long_options[] =
  {
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'V'},
    {NULL, no_argument, 0, 0}
  };

#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
#if defined (HAVE_SETLOCALE)
  setlocale (LC_CTYPE, "");
#endif
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  program_name = av[0];
  xmalloc_set_program_name (program_name);

  expandargv (&ac, &av);

  while ((opt = getopt_long (ac, av, "HhVv", long_options, (int *) NULL)) != EOF)
    {
      switch (opt)
	{
	case 'H':
	case 'h':
	  show_usage (stdout, 0);
	  /*NOTREACHED*/
	case 'v':
	case 'V':
	  print_version ("sysdump");
	  exit (0);
	  /*NOTREACHED*/
	case 0:
	  break;
	default:
	  show_usage (stderr, 1);
	  /*NOTREACHED*/
	}
    }

  /* The input and output files may be named on the command line.  */

  if (optind < ac)
    input_file = av[optind];

  if (!input_file)
    fatal (_("no input file specified"));

  file = fopen (input_file, FOPEN_RB);

  if (!file)
    fatal (_("cannot open input file %s"), input_file);

  module ();
  return 0;
}