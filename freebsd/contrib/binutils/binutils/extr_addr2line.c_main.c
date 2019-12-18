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
 int EOF ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char** addr ; 
 void* base_names ; 
 int /*<<< orphan*/  bfd_init () ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cplus_demangle_name_to_style (char*) ; 
 int /*<<< orphan*/  cplus_demangle_set_style (int) ; 
 void* do_demangle ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  long_options ; 
 int naddr ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  print_version (char*) ; 
 int process_file (char const*,char const*,char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  set_default_bfd_target () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int unknown_demangling ; 
 void* unwind_inlines ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int) ; 
 void* with_functions ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 

int
main (int argc, char **argv)
{
  const char *file_name;
  const char *section_name;
  char *target;
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

  file_name = NULL;
  section_name = NULL;
  target = NULL;
  while ((c = getopt_long (argc, argv, "b:Ce:sfHhij:Vv", long_options, (int *) 0))
	 != EOF)
    {
      switch (c)
	{
	case 0:
	  break;		/* We've been given a long option.  */
	case 'b':
	  target = optarg;
	  break;
	case 'C':
	  do_demangle = TRUE;
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
	case 'e':
	  file_name = optarg;
	  break;
	case 's':
	  base_names = TRUE;
	  break;
	case 'f':
	  with_functions = TRUE;
	  break;
	case 'v':
	case 'V':
	  print_version ("addr2line");
	  break;
	case 'h':
	case 'H':
	  usage (stdout, 0);
	  break;
	case 'i':
	  unwind_inlines = TRUE;
	  break;
	case 'j':
	  section_name = optarg;
	  break;
	default:
	  usage (stderr, 1);
	  break;
	}
    }

  if (file_name == NULL)
    file_name = "a.out";

  addr = argv + optind;
  naddr = argc - optind;

  return process_file (file_name, section_name, target);
}