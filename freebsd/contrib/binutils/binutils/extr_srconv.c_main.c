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
 int /*<<< orphan*/  FOPEN_WB ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abfd ; 
 int base1 ; 
 int base2 ; 
 int /*<<< orphan*/  bfd_check_format_matches (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char***) ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 int /*<<< orphan*/  bfd_fatal (char*) ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_nonfatal (char*) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/  bfd_openr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coff_grok (int /*<<< orphan*/ ) ; 
 int debug ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  file ; 
 int /*<<< orphan*/  fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char**) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
#define  no_argument 128 
 int noprescan ; 
 int optind ; 
 int /*<<< orphan*/  prescan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_version (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 char* program_name ; 
 int quick ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_usage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  wr_module (int /*<<< orphan*/ ) ; 
 char* xmalloc (int) ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 

int
main (int ac, char **av)
{
  int opt;
  static struct option long_options[] =
  {
    {"debug", no_argument, 0, 'd'},
    {"quick", no_argument, 0, 'q'},
    {"noprescan", no_argument, 0, 'n'},
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'V'},
    {NULL, no_argument, 0, 0}
  };
  char **matching;
  char *input_file;
  char *output_file;

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

  while ((opt = getopt_long (ac, av, "dHhVvqn", long_options,
			     (int *) NULL))
	 != EOF)
    {
      switch (opt)
	{
	case 'q':
	  quick = 1;
	  break;
	case 'n':
	  noprescan = 1;
	  break;
	case 'd':
	  debug = 1;
	  break;
	case 'H':
	case 'h':
	  show_usage (stdout, 0);
	  /*NOTREACHED */
	case 'v':
	case 'V':
	  print_version ("srconv");
	  exit (0);
	  /*NOTREACHED */
	case 0:
	  break;
	default:
	  show_usage (stderr, 1);
	  /*NOTREACHED */
	}
    }

  /* The input and output files may be named on the command line.  */
  output_file = NULL;
  if (optind < ac)
    {
      input_file = av[optind];
      ++optind;
      if (optind < ac)
	{
	  output_file = av[optind];
	  ++optind;
	  if (optind < ac)
	    show_usage (stderr, 1);
	  if (strcmp (input_file, output_file) == 0)
	    {
	      fatal (_("input and output files must be different"));
	    }
	}
    }
  else
    input_file = 0;

  if (!input_file)
    {
      fatal (_("no input file specified"));
    }

  if (!output_file)
    {
      /* Take a .o off the input file and stick on a .obj.  If
         it doesn't end in .o, then stick a .obj on anyway */

      int len = strlen (input_file);

      output_file = xmalloc (len + 5);
      strcpy (output_file, input_file);

      if (len > 3
	  && output_file[len - 2] == '.'
	  && output_file[len - 1] == 'o')
	{
	  output_file[len] = 'b';
	  output_file[len + 1] = 'j';
	  output_file[len + 2] = 0;
	}
      else
	{
	  strcat (output_file, ".obj");
	}
    }

  abfd = bfd_openr (input_file, 0);

  if (!abfd)
    bfd_fatal (input_file);

  if (!bfd_check_format_matches (abfd, bfd_object, &matching))
    {
      bfd_nonfatal (input_file);

      if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
	{
	  list_matching_formats (matching);
	  free (matching);
	}
      exit (1);
    }

  file = fopen (output_file, FOPEN_WB);

  if (!file)
    fatal (_("unable to open output file %s"), output_file);

  if (debug)
    printf ("ids %d %d\n", base1, base2);

  tree = coff_grok (abfd);

  if (!noprescan)
    prescan (tree);

  wr_module (tree);
  return 0;
}