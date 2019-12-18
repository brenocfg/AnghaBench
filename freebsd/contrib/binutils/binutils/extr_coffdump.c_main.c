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
struct coff_ofile {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_check_format_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char***) ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 int /*<<< orphan*/  bfd_fatal (char*) ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_nonfatal (char*) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coff_dump (struct coff_ofile*) ; 
 struct coff_ofile* coff_grok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char**) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
#define  no_argument 128 
 int optind ; 
 int /*<<< orphan*/  print_version (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
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
  bfd *abfd;
  struct coff_ofile *tree;
  char **matching;
  char *input_file = NULL;
  int opt;
  static struct option long_options[] =
    {
      { "help", no_argument, 0, 'h' },
      { "version", no_argument, 0, 'V' },
      { NULL, no_argument, 0, 0 }
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

  while ((opt = getopt_long (ac, av, "HhVv", long_options,
			     (int *) NULL))
	 != EOF)
    {
      switch (opt)
	{
	case 'H':
	case 'h':
	  show_usage (stdout, 0);
	  break;
	case 'v':
	case 'V':
	  print_version ("coffdump");
	  exit (0);
	case 0:
	  break;
	default:
	  show_usage (stderr, 1);
	  break;
	}
    }

  if (optind < ac)
    {
      input_file = av[optind];
    }

  if (!input_file)
    fatal (_("no input file specified"));

  abfd = bfd_openr (input_file, 0);

  if (!abfd)
    bfd_fatal (input_file);

  if (! bfd_check_format_matches (abfd, bfd_object, &matching))
    {
      bfd_nonfatal (input_file);

      if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
	{
	  list_matching_formats (matching);
	  free (matching);
	}
      exit (1);
    }

  tree = coff_grok (abfd);

  coff_dump (tree);
  printf ("\n");

  return 0;
}