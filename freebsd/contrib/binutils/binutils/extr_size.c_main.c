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
typedef  scalar_t__ bfd_size_type ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int atol (int /*<<< orphan*/ *) ; 
 int berkeley_format ; 
 int /*<<< orphan*/  bfd_init () ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ decimal ; 
 int /*<<< orphan*/  display_file (char*) ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ hex ; 
 int /*<<< orphan*/  long_options ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ octal ; 
 int /*<<< orphan*/ * optarg ; 
 int optind ; 
 int /*<<< orphan*/  print_version (char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long) ; 
 char* program_name ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ radix ; 
 int return_code ; 
 int /*<<< orphan*/  rprint_number (int,scalar_t__) ; 
 int /*<<< orphan*/  set_default_bfd_target () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ show_help ; 
 int show_totals ; 
 int show_version ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strtol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * target ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 scalar_t__ total_bsssize ; 
 scalar_t__ total_datasize ; 
 scalar_t__ total_textsize ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 

int
main (int argc, char **argv)
{
  int temp;
  int c;

#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
#if defined (HAVE_SETLOCALE)
  setlocale (LC_CTYPE, "");
#endif
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  program_name = *argv;
  xmalloc_set_program_name (program_name);

  expandargv (&argc, &argv);

  bfd_init ();
  set_default_bfd_target ();

  while ((c = getopt_long (argc, argv, "ABHhVvdfotx", long_options,
			   (int *) 0)) != EOF)
    switch (c)
      {
      case 200:		/* --format */
	switch (*optarg)
	  {
	  case 'B':
	  case 'b':
	    berkeley_format = 1;
	    break;
	  case 'S':
	  case 's':
	    berkeley_format = 0;
	    break;
	  default:
	    non_fatal (_("invalid argument to --format: %s"), optarg);
	    usage (stderr, 1);
	  }
	break;

      case 202:		/* --target */
	target = optarg;
	break;

      case 201:		/* --radix */
#ifdef ANSI_LIBRARIES
	temp = strtol (optarg, NULL, 10);
#else
	temp = atol (optarg);
#endif
	switch (temp)
	  {
	  case 10:
	    radix = decimal;
	    break;
	  case 8:
	    radix = octal;
	    break;
	  case 16:
	    radix = hex;
	    break;
	  default:
	    non_fatal (_("Invalid radix: %s\n"), optarg);
	    usage (stderr, 1);
	  }
	break;

      case 'A':
	berkeley_format = 0;
	break;
      case 'B':
	berkeley_format = 1;
	break;
      case 'v':
      case 'V':
	show_version = 1;
	break;
      case 'd':
	radix = decimal;
	break;
      case 'x':
	radix = hex;
	break;
      case 'o':
	radix = octal;
	break;
      case 't':
	show_totals = 1;
	break;
      case 'f': /* FIXME : For sysv68, `-f' means `full format', i.e.
		   `[fname:] M(.text) + N(.data) + O(.bss) + P(.comment) = Q'
		   where `fname: ' appears only if there are >= 2 input files,
		   and M, N, O, P, Q are expressed in decimal by default,
		   hexa or octal if requested by `-x' or `-o'.
		   Just to make things interesting, Solaris also accepts -f,
		   which prints out the size of each allocatable section, the
		   name of the section, and the total of the section sizes.  */
		/* For the moment, accept `-f' silently, and ignore it.  */
	break;
      case 0:
	break;
      case 'h':
      case 'H':
      case '?':
	usage (stderr, 1);
      }

  if (show_version)
    print_version ("size");
  if (show_help)
    usage (stdout, 0);

  if (optind == argc)
    display_file ("a.out");
  else
    for (; optind < argc;)
      display_file (argv[optind++]);

  if (show_totals && berkeley_format)
    {
      bfd_size_type total = total_textsize + total_datasize + total_bsssize;

      rprint_number (7, total_textsize);
      putchar('\t');
      rprint_number (7, total_datasize);
      putchar('\t');
      rprint_number (7, total_bsssize);
      printf (((radix == octal) ? "\t%7lo\t%7lx\t" : "\t%7lu\t%7lx\t"),
	      (unsigned long) total, (unsigned long) total);
      fputs ("(TOTALS)\n", stdout);
    }

  return return_code;
}