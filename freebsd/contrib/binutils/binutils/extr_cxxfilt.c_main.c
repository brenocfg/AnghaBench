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
typedef  int /*<<< orphan*/  mbuffer ;
typedef  enum demangling_styles { ____Placeholder_demangling_styles } demangling_styles ;

/* Variables and functions */
 int /*<<< orphan*/  DMGL_PARAMS ; 
 int /*<<< orphan*/  DMGL_TYPES ; 
 int /*<<< orphan*/  DMGL_VERBOSE ; 
 int EOF ; 
 scalar_t__ ISALNUM (int) ; 
#define  arm_demangling 136 
#define  auto_demangling 135 
 int cplus_demangle_name_to_style (char*) ; 
 int /*<<< orphan*/  cplus_demangle_set_style (int) ; 
 int current_demangling_style ; 
 int /*<<< orphan*/  demangle_it (char*) ; 
#define  edg_demangling 134 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int getchar () ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
#define  gnat_demangling 133 
#define  gnu_demangling 132 
#define  gnu_v3_demangling 131 
#define  hp_demangling 130 
 char* hp_symbol_characters () ; 
#define  java_demangling 129 
 int /*<<< orphan*/  long_options ; 
#define  lucid_demangling 128 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  print_version (char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  putchar (int) ; 
 char* standard_symbol_characters () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strchr (char const*,int) ; 
 int strip_underscore ; 
 int unknown_demangling ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 

int
main (int argc, char **argv)
{
  int c;
  const char *valid_symbols;
  enum demangling_styles style = auto_demangling;

  program_name = argv[0];
  xmalloc_set_program_name (program_name);

  expandargv (&argc, &argv);

  while ((c = getopt_long (argc, argv, "_hinps:tv", long_options, (int *) 0)) != EOF)
    {
      switch (c)
	{
	case '?':
	  usage (stderr, 1);
	  break;
	case 'h':
	  usage (stdout, 0);
	case 'n':
	  strip_underscore = 0;
	  break;
	case 'p':
	  flags &= ~ DMGL_PARAMS;
	  break;
	case 't':
	  flags |= DMGL_TYPES;
	  break;
	case 'i':
	  flags &= ~ DMGL_VERBOSE;
	  break;
	case 'v':
	  print_version ("c++filt");
	  return 0;
	case '_':
	  strip_underscore = 1;
	  break;
	case 's':
	  style = cplus_demangle_name_to_style (optarg);
	  if (style == unknown_demangling)
	    {
	      fprintf (stderr, "%s: unknown demangling style `%s'\n",
		       program_name, optarg);
	      return 1;
	    }
	  cplus_demangle_set_style (style);
	  break;
	}
    }

  if (optind < argc)
    {
      for ( ; optind < argc; optind++)
	{
	  demangle_it (argv[optind]);
	  putchar ('\n');
	}

      return 0;
    }

  switch (current_demangling_style)
    {
    case gnu_demangling:
    case lucid_demangling:
    case arm_demangling:
    case java_demangling:
    case edg_demangling:
    case gnat_demangling:
    case gnu_v3_demangling:
    case auto_demangling:
      valid_symbols = standard_symbol_characters ();
      break;
    case hp_demangling:
      valid_symbols = hp_symbol_characters ();
      break;
    default:
      /* Folks should explicitly indicate the appropriate alphabet for
	 each demangling.  Providing a default would allow the
	 question to go unconsidered.  */
      fatal ("Internal error: no symbol alphabet for current style");
    }

  for (;;)
    {
      static char mbuffer[32767];
      unsigned i = 0;

      c = getchar ();
      /* Try to read a mangled name.  */
      while (c != EOF && (ISALNUM (c) || strchr (valid_symbols, c)))
	{
	  if (i >= sizeof (mbuffer) - 1)
	    break;
	  mbuffer[i++] = c;
	  c = getchar ();
	}

      if (i > 0)
	{
	  mbuffer[i] = 0;
	  demangle_it (mbuffer);
	}

      if (c == EOF)
	break;

      /* Echo the whitespace characters so that the output looks
	 like the input, only with the mangled names demangled.  */
      putchar (c);
      if (c == '\n')
	fflush (stdout);
    }

  fflush (stdout);
  return 0;
}