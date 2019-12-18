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
typedef  void* bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ENDIAN_BIG ; 
 int /*<<< orphan*/  BFD_ENDIAN_LITTLE ; 
 int /*<<< orphan*/  END_PROGRESS (char*) ; 
 int EOF ; 
 void* FALSE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
#define  OPTION_ADJUST_VMA 131 
#define  OPTION_ENDIAN 130 
#define  OPTION_START_ADDRESS 129 
#define  OPTION_STOP_ADDRESS 128 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  START_PROGRESS (char*,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_include_path (char*) ; 
 void* adjust_section_vma ; 
 int /*<<< orphan*/  bfd_init () ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* concat (char*,char*,char*,int /*<<< orphan*/ *) ; 
 int cplus_demangle_name_to_style (char*) ; 
 int /*<<< orphan*/  cplus_demangle_set_style (int) ; 
 char* default_target ; 
 void* disassemble ; 
 void* disassemble_all ; 
 void* disassemble_zeroes ; 
 char* disassembler_options ; 
 int /*<<< orphan*/  display_file (char*,char*) ; 
 int display_info () ; 
 int do_debug_abbrevs ; 
 int do_debug_aranges ; 
 int do_debug_frames ; 
 int do_debug_info ; 
 int do_debug_lines ; 
 int do_debug_loc ; 
 int do_debug_macinfo ; 
 int do_debug_pubnames ; 
 int do_debug_ranges ; 
 int do_debug_str ; 
 void* do_demangle ; 
 void* dump_ar_hdrs ; 
 int dump_debugging ; 
 int dump_debugging_tags ; 
 void* dump_dwarf_section_info ; 
 void* dump_dynamic_reloc_info ; 
 void* dump_dynamic_symtab ; 
 void* dump_file_header ; 
 void* dump_private_headers ; 
 void* dump_reloc_info ; 
 void* dump_section_contents ; 
 void* dump_section_headers ; 
 void* dump_stab_section_info ; 
 void* dump_symtab ; 
 int /*<<< orphan*/  endian ; 
 int exit_status ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 void* formats_info ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  long_options ; 
 char* machine ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,...) ; 
 char** only ; 
 int only_size ; 
 int only_used ; 
 char* optarg ; 
 int optind ; 
 void* parse_vma (char*,char*) ; 
 int /*<<< orphan*/  print_version (char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  set_default_bfd_target () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 void* show_version ; 
 void* start_address ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 void* stop_address ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int unknown_demangling ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int) ; 
 void* wide_output ; 
 void* with_line_numbers ; 
 void* with_source_code ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 
 char** xrealloc (char**,int) ; 

int
main (int argc, char **argv)
{
  int c;
  char *target = default_target;
  bfd_boolean seenflag = FALSE;

#if defined (HAVE_SETLOCALE)
#if defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
  setlocale (LC_CTYPE, "");
#endif

  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  program_name = *argv;
  xmalloc_set_program_name (program_name);

  START_PROGRESS (program_name, 0);

  expandargv (&argc, &argv);

  bfd_init ();
  set_default_bfd_target ();

  while ((c = getopt_long (argc, argv, "pib:m:M:VvCdDlfaHhrRtTxsSI:j:wE:zgeGW",
			   long_options, (int *) 0))
	 != EOF)
    {
      switch (c)
	{
	case 0:
	  break;		/* We've been given a long option.  */
	case 'm':
	  machine = optarg;
	  break;
	case 'M':
	  if (disassembler_options)
	    /* Ignore potential memory leak for now.  */
	    disassembler_options = concat (disassembler_options, ",",
					   optarg, NULL);
	  else
	    disassembler_options = optarg;
	  break;
	case 'j':
	  if (only_used == only_size)
	    {
	      only_size += 8;
	      only = xrealloc (only, only_size * sizeof (char *));
	    }
	  only [only_used++] = optarg;
	  break;
	case 'l':
	  with_line_numbers = TRUE;
	  break;
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
	case 'w':
	  wide_output = TRUE;
	  break;
	case OPTION_ADJUST_VMA:
	  adjust_section_vma = parse_vma (optarg, "--adjust-vma");
	  break;
	case OPTION_START_ADDRESS:
	  start_address = parse_vma (optarg, "--start-address");
	  break;
	case OPTION_STOP_ADDRESS:
	  stop_address = parse_vma (optarg, "--stop-address");
	  break;
	case 'E':
	  if (strcmp (optarg, "B") == 0)
	    endian = BFD_ENDIAN_BIG;
	  else if (strcmp (optarg, "L") == 0)
	    endian = BFD_ENDIAN_LITTLE;
	  else
	    {
	      non_fatal (_("unrecognized -E option"));
	      usage (stderr, 1);
	    }
	  break;
	case OPTION_ENDIAN:
	  if (strncmp (optarg, "big", strlen (optarg)) == 0)
	    endian = BFD_ENDIAN_BIG;
	  else if (strncmp (optarg, "little", strlen (optarg)) == 0)
	    endian = BFD_ENDIAN_LITTLE;
	  else
	    {
	      non_fatal (_("unrecognized --endian type `%s'"), optarg);
	      usage (stderr, 1);
	    }
	  break;

	case 'f':
	  dump_file_header = TRUE;
	  seenflag = TRUE;
	  break;
	case 'i':
	  formats_info = TRUE;
	  seenflag = TRUE;
	  break;
	case 'I':
	  add_include_path (optarg);
	  break;
	case 'p':
	  dump_private_headers = TRUE;
	  seenflag = TRUE;
	  break;
	case 'x':
	  dump_private_headers = TRUE;
	  dump_symtab = TRUE;
	  dump_reloc_info = TRUE;
	  dump_file_header = TRUE;
	  dump_ar_hdrs = TRUE;
	  dump_section_headers = TRUE;
	  seenflag = TRUE;
	  break;
	case 't':
	  dump_symtab = TRUE;
	  seenflag = TRUE;
	  break;
	case 'T':
	  dump_dynamic_symtab = TRUE;
	  seenflag = TRUE;
	  break;
	case 'd':
	  disassemble = TRUE;
	  seenflag = TRUE;
	  break;
	case 'z':
	  disassemble_zeroes = TRUE;
	  break;
	case 'D':
	  disassemble = TRUE;
	  disassemble_all = TRUE;
	  seenflag = TRUE;
	  break;
	case 'S':
	  disassemble = TRUE;
	  with_source_code = TRUE;
	  seenflag = TRUE;
	  break;
	case 'g':
	  dump_debugging = 1;
	  seenflag = TRUE;
	  break;
	case 'e':
	  dump_debugging = 1;
	  dump_debugging_tags = 1;
	  do_demangle = TRUE;
	  seenflag = TRUE;
	  break;
	case 'W':
	  dump_dwarf_section_info = TRUE;
	  seenflag = TRUE;
	  do_debug_info = 1;
	  do_debug_abbrevs = 1;
	  do_debug_lines = 1;
	  do_debug_pubnames = 1;
	  do_debug_aranges = 1;
	  do_debug_ranges = 1;
	  do_debug_frames = 1;
	  do_debug_macinfo = 1;
	  do_debug_str = 1;
	  do_debug_loc = 1;
	  break;
	case 'G':
	  dump_stab_section_info = TRUE;
	  seenflag = TRUE;
	  break;
	case 's':
	  dump_section_contents = TRUE;
	  seenflag = TRUE;
	  break;
	case 'r':
	  dump_reloc_info = TRUE;
	  seenflag = TRUE;
	  break;
	case 'R':
	  dump_dynamic_reloc_info = TRUE;
	  seenflag = TRUE;
	  break;
	case 'a':
	  dump_ar_hdrs = TRUE;
	  seenflag = TRUE;
	  break;
	case 'h':
	  dump_section_headers = TRUE;
	  seenflag = TRUE;
	  break;
	case 'H':
	  usage (stdout, 0);
	  seenflag = TRUE;
	case 'v':
	case 'V':
	  show_version = TRUE;
	  seenflag = TRUE;
	  break;

	default:
	  usage (stderr, 1);
	}
    }

  if (show_version)
    print_version ("objdump");

  if (!seenflag)
    usage (stderr, 2);

  if (formats_info)
    exit_status = display_info ();
  else
    {
      if (optind == argc)
	display_file ("a.out", target);
      else
	for (; optind < argc;)
	  display_file (argv[optind++], target);
    }

  END_PROGRESS (program_name);

  return exit_status;
}