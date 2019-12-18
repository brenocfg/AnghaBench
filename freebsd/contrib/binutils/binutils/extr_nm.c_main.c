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
typedef  enum demangling_styles { ____Placeholder_demangling_styles } demangling_styles ;

/* Variables and functions */
 int /*<<< orphan*/  END_PROGRESS (char*) ; 
 int EOF ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
#define  OPTION_TARGET 128 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  PROGRESS (int) ; 
 int /*<<< orphan*/  START_PROGRESS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_init () ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cplus_demangle_name_to_style (char*) ; 
 int /*<<< orphan*/  cplus_demangle_set_style (int) ; 
 int /*<<< orphan*/  display_file (char*) ; 
 int do_demangle ; 
 int dynamic ; 
 int /*<<< orphan*/  environ ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int external_only ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,...) ; 
 int filename_per_file ; 
 int filename_per_symbol ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int line_numbers ; 
 int /*<<< orphan*/  long_options ; 
 int no_sort ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,...) ; 
 char* optarg ; 
 int optind ; 
 int print_armap ; 
 int print_debug_syms ; 
 int print_size ; 
 int /*<<< orphan*/  print_version (char*) ; 
 char* program_name ; 
 int reverse_sort ; 
 scalar_t__ sbrk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_default_bfd_target () ; 
 int /*<<< orphan*/  set_output_format (char*) ; 
 int /*<<< orphan*/  set_print_radix (char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ show_stats ; 
 int show_version ; 
 scalar_t__ sort_by_size ; 
 int sort_numerically ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* target ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int undefined_only ; 
 int unknown_demangling ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 

int
main (int argc, char **argv)
{
  int c;
  int retval;

#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
#if defined (HAVE_SETLOCALE)
  setlocale (LC_CTYPE, "");
  setlocale (LC_COLLATE, "");
#endif
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  program_name = *argv;
  xmalloc_set_program_name (program_name);

  START_PROGRESS (program_name, 0);

  expandargv (&argc, &argv);

  bfd_init ();
  set_default_bfd_target ();

  while ((c = getopt_long (argc, argv, "aABCDef:gHhlnopPrSst:uvVvX:",
			   long_options, (int *) 0)) != EOF)
    {
      switch (c)
	{
	case 'a':
	  print_debug_syms = 1;
	  break;
	case 'A':
	case 'o':
	  filename_per_symbol = 1;
	  break;
	case 'B':		/* For MIPS compatibility.  */
	  set_output_format ("bsd");
	  break;
	case 'C':
	  do_demangle = 1;
	  if (optarg != NULL)
	    {
	      enum demangling_styles style;

	      style = cplus_demangle_name_to_style (optarg);
	      if (style == unknown_demangling)
		fatal (_("unknown demangling style `%s'"),
		       optarg);

	      cplus_demangle_set_style (style);
	    }
	  break;
	case 'D':
	  dynamic = 1;
	  break;
	case 'e':
	  /* Ignored for HP/UX compatibility.  */
	  break;
	case 'f':
	  set_output_format (optarg);
	  break;
	case 'g':
	  external_only = 1;
	  break;
	case 'H':
	case 'h':
	  usage (stdout, 0);
	case 'l':
	  line_numbers = 1;
	  break;
	case 'n':
	case 'v':
	  sort_numerically = 1;
	  break;
	case 'p':
	  no_sort = 1;
	  break;
	case 'P':
	  set_output_format ("posix");
	  break;
	case 'r':
	  reverse_sort = 1;
	  break;
	case 's':
	  print_armap = 1;
	  break;
	case 'S':
	  print_size = 1;
	  break;
	case 't':
	  set_print_radix (optarg);
	  break;
	case 'u':
	  undefined_only = 1;
	  break;
	case 'V':
	  show_version = 1;
	  break;
	case 'X':
	  /* Ignored for (partial) AIX compatibility.  On AIX, the
	     argument has values 32, 64, or 32_64, and specifies that
	     only 32-bit, only 64-bit, or both kinds of objects should
	     be examined.  The default is 32.  So plain AIX nm on a
	     library archive with both kinds of objects will ignore
	     the 64-bit ones.  For GNU nm, the default is and always
	     has been -X 32_64, and other options are not supported.  */
	  if (strcmp (optarg, "32_64") != 0)
	    fatal (_("Only -X 32_64 is supported"));
	  break;

	case OPTION_TARGET:	/* --target */
	  target = optarg;
	  break;

	case 0:		/* A long option that just sets a flag.  */
	  break;

	default:
	  usage (stderr, 1);
	}
    }

  if (show_version)
    print_version ("nm");

  if (sort_by_size && undefined_only)
    {
      non_fatal (_("Using the --size-sort and --undefined-only options together"));
      non_fatal (_("will produce no output, since undefined symbols have no size."));
      return 0;
    }

  /* OK, all options now parsed.  If no filename specified, do a.out.  */
  if (optind == argc)
    return !display_file ("a.out");

  retval = 0;

  if (argc - optind > 1)
    filename_per_file = 1;

  /* We were given several filenames to do.  */
  while (optind < argc)
    {
      PROGRESS (1);
      if (!display_file (argv[optind++]))
	retval++;
    }

  END_PROGRESS (program_name);

#ifdef HAVE_SBRK
  if (show_stats)
    {
      char *lim = (char *) sbrk (0);

      non_fatal (_("data size %ld"), (long) (lim - (char *) &environ));
    }
#endif

  exit (retval);
  return retval;
}