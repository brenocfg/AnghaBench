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
typedef  void* bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char*,char*) ; 
 int /*<<< orphan*/  END_PROGRESS (char*) ; 
 void* FALSE ; 
 scalar_t__ FILENAME_CMP (char*,char*) ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  START_PROGRESS (char*,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ar_emul_parse_arg (char*) ; 
 void* ar_truncate ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  bfd_init () ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ counted_name_counter ; 
 void* counted_name_mode ; 
 int /*<<< orphan*/  delete_members (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  extract_file ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ) ; 
 void* full_pathname ; 
 int is_ranlib ; 
 int /*<<< orphan*/  map_over_members (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  move_members (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  mri_emul () ; 
 int mri_mode ; 
 int newer_only ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/ * open_inarch (char*,char*) ; 
 void* operation_alters_arch ; 
 int /*<<< orphan*/ * output_filename ; 
 scalar_t__ pos_after ; 
 scalar_t__ pos_before ; 
 scalar_t__ pos_default ; 
 char* posname ; 
 scalar_t__ postype ; 
 int preserve_dates ; 
 int /*<<< orphan*/  print_contents ; 
 int /*<<< orphan*/  print_descr ; 
 int /*<<< orphan*/  print_version (char*) ; 
 char* program_name ; 
 int ranlib_only (char*) ; 
 int ranlib_touch (char*) ; 
 int /*<<< orphan*/  remove_output ; 
 int /*<<< orphan*/  replace_members (int /*<<< orphan*/ *,char**,int) ; 
 int /*<<< orphan*/  set_default_bfd_target () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int silent_create ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int) ; 
 int verbose ; 
 int write_armap ; 
 int /*<<< orphan*/  xatexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xexit (int) ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 

int
main (int argc, char **argv)
{
  char *arg_ptr;
  char c;
  enum
    {
      none = 0, delete, replace, print_table,
      print_files, extract, move, quick_append
    } operation = none;
  int arg_index;
  char **files;
  int file_count;
  char *inarch_filename;
  int show_version;
  int i;
  int do_posix = 0;

#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
#if defined (HAVE_SETLOCALE)
  setlocale (LC_CTYPE, "");
#endif
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  program_name = argv[0];
  xmalloc_set_program_name (program_name);

  expandargv (&argc, &argv);

  if (is_ranlib < 0)
    {
      char *temp;

      temp = strrchr (program_name, '/');
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
      {
	/* We could have foo/bar\\baz, or foo\\bar, or d:bar.  */
	char *bslash = strrchr (program_name, '\\');
	if (temp == NULL || (bslash != NULL && bslash > temp))
	  temp = bslash;
	if (temp == NULL && program_name[0] != '\0' && program_name[1] == ':')
	  temp = program_name + 1;
      }
#endif
      if (temp == NULL)
	temp = program_name;
      else
	++temp;
      if (strlen (temp) >= 6
	  && FILENAME_CMP (temp + strlen (temp) - 6, "ranlib") == 0)
	is_ranlib = 1;
      else
	is_ranlib = 0;
    }

  if (argc > 1 && argv[1][0] == '-')
    {
      if (strcmp (argv[1], "--help") == 0)
	usage (1);
      else if (strcmp (argv[1], "--version") == 0)
	{
	  if (is_ranlib)
	    print_version ("ranlib");
	  else
	    print_version ("ar");
	}
    }

  START_PROGRESS (program_name, 0);

  bfd_init ();
  set_default_bfd_target ();

  show_version = 0;

  xatexit (remove_output);

  for (i = 1; i < argc; i++)
    if (! ar_emul_parse_arg (argv[i]))
      break;
  argv += (i - 1);
  argc -= (i - 1);

  if (is_ranlib)
    {
      int status = 0;
      bfd_boolean touch = FALSE;

      if (argc < 2
	  || strcmp (argv[1], "--help") == 0
	  || strcmp (argv[1], "-h") == 0
	  || strcmp (argv[1], "-H") == 0)
	usage (0);
      if (strcmp (argv[1], "-V") == 0
	  || strcmp (argv[1], "-v") == 0
	  || CONST_STRNEQ (argv[1], "--v"))
	print_version ("ranlib");
      arg_index = 1;
      if (strcmp (argv[1], "-t") == 0)
	{
	  ++arg_index;
	  touch = TRUE;
	}
      while (arg_index < argc)
	{
	  if (! touch)
	    status |= ranlib_only (argv[arg_index]);
	  else
	    status |= ranlib_touch (argv[arg_index]);
	  ++arg_index;
	}
      xexit (status);
    }

  if (argc == 2 && strcmp (argv[1], "-M") == 0)
    {
      mri_emul ();
      xexit (0);
    }

  if (argc < 2)
    usage (0);

  arg_index = 1;
  arg_ptr = argv[arg_index];

  if (*arg_ptr == '-')
    {
      /* When the first option starts with '-' we support POSIX-compatible
	 option parsing.  */
      do_posix = 1;
      ++arg_ptr;			/* compatibility */
    }

  do
    {
      while ((c = *arg_ptr++) != '\0')
	{
	  switch (c)
	    {
	    case 'd':
	    case 'm':
	    case 'p':
	    case 'q':
	    case 'r':
	    case 't':
	    case 'x':
	      if (operation != none)
		fatal (_("two different operation options specified"));
	      switch (c)
		{
		case 'd':
		  operation = delete;
		  operation_alters_arch = TRUE;
		  break;
		case 'm':
		  operation = move;
		  operation_alters_arch = TRUE;
		  break;
		case 'p':
		  operation = print_files;
		  break;
		case 'q':
		  operation = quick_append;
		  operation_alters_arch = TRUE;
		  break;
		case 'r':
		  operation = replace;
		  operation_alters_arch = TRUE;
		  break;
		case 't':
		  operation = print_table;
		  break;
		case 'x':
		  operation = extract;
		  break;
		}
	    case 'l':
	      break;
	    case 'c':
	      silent_create = 1;
	      break;
	    case 'o':
	      preserve_dates = 1;
	      break;
	    case 'V':
	      show_version = TRUE;
	      break;
	    case 's':
	      write_armap = 1;
	      break;
	    case 'S':
	      write_armap = -1;
	      break;
	    case 'u':
	      newer_only = 1;
	      break;
	    case 'v':
	      verbose = 1;
	      break;
	    case 'a':
	      postype = pos_after;
	      break;
	    case 'b':
	      postype = pos_before;
	      break;
	    case 'i':
	      postype = pos_before;
	      break;
	    case 'M':
	      mri_mode = 1;
	      break;
	    case 'N':
	      counted_name_mode = TRUE;
	      break;
	    case 'f':
	      ar_truncate = TRUE;
	      break;
	    case 'P':
	      full_pathname = TRUE;
	      break;
	    default:
	      /* xgettext:c-format */
	      non_fatal (_("illegal option -- %c"), c);
	      usage (0);
	    }
	}

      /* With POSIX-compatible option parsing continue with the next
	 argument if it starts with '-'.  */
      if (do_posix && arg_index + 1 < argc && argv[arg_index + 1][0] == '-')
	arg_ptr = argv[++arg_index] + 1;
      else
	do_posix = 0;
    }
  while (do_posix);

  if (show_version)
    print_version ("ar");

  ++arg_index;
  if (arg_index >= argc)
    usage (0);

  if (mri_mode)
    {
      mri_emul ();
    }
  else
    {
      bfd *arch;

      /* We don't use do_quick_append any more.  Too many systems
	 expect ar to always rebuild the symbol table even when q is
	 used.  */

      /* We can't write an armap when using ar q, so just do ar r
         instead.  */
      if (operation == quick_append && write_armap)
	operation = replace;

      if ((operation == none || operation == print_table)
	  && write_armap == 1)
	xexit (ranlib_only (argv[arg_index]));

      if (operation == none)
	fatal (_("no operation specified"));

      if (newer_only && operation != replace)
	fatal (_("`u' is only meaningful with the `r' option."));

      if (postype != pos_default)
	posname = argv[arg_index++];

      if (counted_name_mode)
	{
	  if (operation != extract && operation != delete)
	     fatal (_("`N' is only meaningful with the `x' and `d' options."));
	  counted_name_counter = atoi (argv[arg_index++]);
	  if (counted_name_counter <= 0)
	    fatal (_("Value for `N' must be positive."));
	}

      inarch_filename = argv[arg_index++];

      files = arg_index < argc ? argv + arg_index : NULL;
      file_count = argc - arg_index;

      arch = open_inarch (inarch_filename,
			  files == NULL ? (char *) NULL : files[0]);

      switch (operation)
	{
	case print_table:
	  map_over_members (arch, print_descr, files, file_count);
	  break;

	case print_files:
	  map_over_members (arch, print_contents, files, file_count);
	  break;

	case extract:
	  map_over_members (arch, extract_file, files, file_count);
	  break;

	case delete:
	  if (files != NULL)
	    delete_members (arch, files);
	  else
	    output_filename = NULL;
	  break;

	case move:
	  if (files != NULL)
	    move_members (arch, files);
	  else
	    output_filename = NULL;
	  break;

	case replace:
	case quick_append:
	  if (files != NULL || write_armap > 0)
	    replace_members (arch, files, operation == quick_append);
	  else
	    output_filename = NULL;
	  break;

	  /* Shouldn't happen! */
	default:
	  /* xgettext:c-format */
	  fatal (_("internal error -- this option not implemented"));
	}
    }

  END_PROGRESS (program_name);

  xexit (0);
  return 0;
}