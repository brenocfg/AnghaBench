#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dyn_string_t ;
struct TYPE_5__ {char* s; int length; } ;

/* Variables and functions */
#define  CYGWIN_TARGET 143 
 int EOF ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
#define  MINGW_TARGET 142 
#define  OPTION_BASE_FILE 141 
#define  OPTION_DEF 140 
#define  OPTION_DLLNAME 139 
#define  OPTION_DLLTOOL_NAME 138 
#define  OPTION_DRIVER_FLAGS 137 
#define  OPTION_DRIVER_NAME 136 
#define  OPTION_DRY_RUN 135 
#define  OPTION_EXPORT_ALL_SYMS 134 
#define  OPTION_IMAGE_BASE 133 
#define  OPTION_MNO_CYGWIN 132 
#define  OPTION_OUTPUT_EXP 131 
#define  OPTION_OUTPUT_LIB 130 
#define  OPTION_TARGET 129 
#define  OPTION_VERSION 128 
 int /*<<< orphan*/  PACKAGE ; 
 int UNKNOWN_TARGET ; 
 char* _ (char*) ; 
 char* base_file_name ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* choose_temp_base () ; 
 int /*<<< orphan*/  cleanup_and_exit (int) ; 
 char* cygwin_driver_flags ; 
 char* deduce_name (char*) ; 
 char* def_file_name ; 
 int delete_base_file ; 
 int delete_def_file ; 
 int delete_exp_file ; 
 char* dll_file_name ; 
 char* dll_name ; 
 char* dlltool_name ; 
 int dontdeltemps ; 
 char* driver_name ; 
 int dry_run ; 
 int /*<<< orphan*/  dyn_string_append_cstr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dyn_string_delete (TYPE_1__*) ; 
 TYPE_1__* dyn_string_new (int) ; 
 char* entry_point ; 
 int /*<<< orphan*/  exit (int) ; 
 char* exp_file_name ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* generic_driver_flags ; 
 int getopt_long_only (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  long_options ; 
 char* mingw32_driver_flags ; 
 char* mybasename (char*) ; 
 void* optarg ; 
 scalar_t__ opterr ; 
 int optind ; 
 int /*<<< orphan*/  print_version (char*) ; 
 char* prog_name ; 
 scalar_t__ run (char*,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 unsigned long strhash (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strstr (char*,char*) ; 
 char* target ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verbose ; 
 int /*<<< orphan*/  warn (char*) ; 
 int which_target ; 
 scalar_t__ xmalloc (size_t) ; 
 char* xstrdup (char*) ; 

int
main (int argc, char **argv)
{
  int c;
  int i;

  char **saved_argv = 0;
  int cmdline_len = 0;

  int export_all = 0;

  int *dlltool_arg_indices;
  int *driver_arg_indices;

  char *driver_flags = 0;
  char *output_lib_file_name = 0;

  dyn_string_t dlltool_cmdline;
  dyn_string_t driver_cmdline;

  int def_file_seen = 0;

  char *image_base_str = 0;

  prog_name = argv[0];

#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
#if defined (HAVE_SETLOCALE)
  setlocale (LC_CTYPE, "");
#endif
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  expandargv (&argc, &argv);

  saved_argv = (char **) xmalloc (argc * sizeof (char*));
  dlltool_arg_indices = (int *) xmalloc (argc * sizeof (int));
  driver_arg_indices = (int *) xmalloc (argc * sizeof (int));
  for (i = 0; i < argc; ++i)
    {
      size_t len = strlen (argv[i]);
      char *arg = (char *) xmalloc (len + 1);
      strcpy (arg, argv[i]);
      cmdline_len += len;
      saved_argv[i] = arg;
      dlltool_arg_indices[i] = 0;
      driver_arg_indices[i] = 1;
    }
  cmdline_len++;

  /* We recognize dllwrap and dlltool options, and everything else is
     passed onto the language driver (eg., to GCC). We collect options
     to dlltool and driver in dlltool_args and driver_args.  */

  opterr = 0;
  while ((c = getopt_long_only (argc, argv, "nkAqve:Uho:l:L:I:",
				long_options, (int *) 0)) != EOF)
    {
      int dlltool_arg;
      int driver_arg;
      int single_word_option_value_pair;

      dlltool_arg = 0;
      driver_arg = 1;
      single_word_option_value_pair = 0;

      if (c != '?')
	{
	  /* We recognize this option, so it has to be either dllwrap or
	     dlltool option. Do not pass to driver unless it's one of the
	     generic options that are passed to all the tools (such as -v)
	     which are dealt with later.  */
	  driver_arg = 0;
	}

      /* deal with generic and dllwrap options first.  */
      switch (c)
	{
	case 'h':
	  usage (stdout, 0);
	  break;
	case 'q':
	  verbose = 0;
	  break;
	case 'v':
	  verbose = 1;
	  break;
	case OPTION_VERSION:
	  print_version (prog_name);
	  break;
	case 'e':
	  entry_point = optarg;
	  break;
	case OPTION_IMAGE_BASE:
	  image_base_str = optarg;
	  break;
	case OPTION_DEF:
	  def_file_name = optarg;
	  def_file_seen = 1;
	  delete_def_file = 0;
	  break;
	case 'n':
	  dontdeltemps = 1;
	  dlltool_arg = 1;
	  break;
	case 'o':
	  dll_file_name = optarg;
	  break;
	case 'I':
	case 'l':
	case 'L':
	  driver_arg = 1;
	  break;
	case OPTION_DLLNAME:
	  dll_name = optarg;
	  break;
	case OPTION_DRY_RUN:
	  dry_run = 1;
	  break;
	case OPTION_DRIVER_NAME:
	  driver_name = optarg;
	  break;
	case OPTION_DRIVER_FLAGS:
	  driver_flags = optarg;
	  break;
	case OPTION_DLLTOOL_NAME:
	  dlltool_name = optarg;
	  break;
	case OPTION_TARGET:
	  target = optarg;
	  break;
	case OPTION_MNO_CYGWIN:
	  target = "i386-mingw32";
	  break;
	case OPTION_BASE_FILE:
	  base_file_name = optarg;
	  delete_base_file = 0;
	  break;
	case OPTION_OUTPUT_EXP:
	  exp_file_name = optarg;
	  delete_exp_file = 0;
	  break;
	case OPTION_EXPORT_ALL_SYMS:
	  export_all = 1;
	  break;
	case OPTION_OUTPUT_LIB:
	  output_lib_file_name = optarg;
	  break;
	case '?':
	  break;
	default:
	  dlltool_arg = 1;
	  break;
	}

      /* Handle passing through --option=value case.  */
      if (optarg
	  && saved_argv[optind-1][0] == '-'
	  && saved_argv[optind-1][1] == '-'
	  && strchr (saved_argv[optind-1], '='))
	single_word_option_value_pair = 1;

      if (dlltool_arg)
	{
	  dlltool_arg_indices[optind-1] = 1;
	  if (optarg && ! single_word_option_value_pair)
	    {
	      dlltool_arg_indices[optind-2] = 1;
	    }
	}

      if (! driver_arg)
	{
	  driver_arg_indices[optind-1] = 0;
	  if (optarg && ! single_word_option_value_pair)
	    {
	      driver_arg_indices[optind-2] = 0;
	    }
	}
    }

  /* Sanity checks.  */
  if (! dll_name && ! dll_file_name)
    {
      warn (_("Must provide at least one of -o or --dllname options"));
      exit (1);
    }
  else if (! dll_name)
    {
      dll_name = xstrdup (mybasename (dll_file_name));
    }
  else if (! dll_file_name)
    {
      dll_file_name = xstrdup (dll_name);
    }

  /* Deduce driver-name and dlltool-name from our own.  */
  if (driver_name == NULL)
    driver_name = deduce_name ("gcc");

  if (dlltool_name == NULL)
    dlltool_name = deduce_name ("dlltool");

  if (! def_file_seen)
    {
      char *fileprefix = choose_temp_base ();

      def_file_name = (char *) xmalloc (strlen (fileprefix) + 5);
      sprintf (def_file_name, "%s.def",
	       (dontdeltemps) ? mybasename (fileprefix) : fileprefix);
      delete_def_file = 1;
      free (fileprefix);
      delete_def_file = 1;
      warn (_("no export definition file provided.\n\
Creating one, but that may not be what you want"));
    }

  /* Set the target platform.  */
  if (strstr (target, "cygwin"))
    which_target = CYGWIN_TARGET;
  else if (strstr (target, "mingw"))
    which_target = MINGW_TARGET;
  else
    which_target = UNKNOWN_TARGET;

  /* Re-create the command lines as a string, taking care to quote stuff.  */
  dlltool_cmdline = dyn_string_new (cmdline_len);
  if (verbose)
    dyn_string_append_cstr (dlltool_cmdline, " -v");

  dyn_string_append_cstr (dlltool_cmdline, " --dllname ");
  dyn_string_append_cstr (dlltool_cmdline, dll_name);

  for (i = 1; i < argc; ++i)
    {
      if (dlltool_arg_indices[i])
	{
	  char *arg = saved_argv[i];
	  int quote = (strchr (arg, ' ') || strchr (arg, '\t'));
	  dyn_string_append_cstr (dlltool_cmdline,
	                     (quote) ? " \"" : " ");
	  dyn_string_append_cstr (dlltool_cmdline, arg);
	  dyn_string_append_cstr (dlltool_cmdline,
	                     (quote) ? "\"" : "");
	}
    }

  driver_cmdline = dyn_string_new (cmdline_len);
  if (! driver_flags || strlen (driver_flags) == 0)
    {
      switch (which_target)
	{
	case CYGWIN_TARGET:
	  driver_flags = cygwin_driver_flags;
	  break;

	case MINGW_TARGET:
	  driver_flags = mingw32_driver_flags;
	  break;

	default:
	  driver_flags = generic_driver_flags;
	  break;
	}
    }
  dyn_string_append_cstr (driver_cmdline, driver_flags);
  dyn_string_append_cstr (driver_cmdline, " -o ");
  dyn_string_append_cstr (driver_cmdline, dll_file_name);

  if (! entry_point || strlen (entry_point) == 0)
    {
      switch (which_target)
	{
	case CYGWIN_TARGET:
	  entry_point = "__cygwin_dll_entry@12";
	  break;

	case MINGW_TARGET:
	  entry_point = "_DllMainCRTStartup@12";
	  break;

	default:
	  entry_point = "_DllMain@12";
	  break;
	}
    }
  dyn_string_append_cstr (driver_cmdline, " -Wl,-e,");
  dyn_string_append_cstr (driver_cmdline, entry_point);
  dyn_string_append_cstr (dlltool_cmdline, " --exclude-symbol=");
  dyn_string_append_cstr (dlltool_cmdline,
                    (entry_point[0] == '_') ? entry_point+1 : entry_point);

  if (! image_base_str || strlen (image_base_str) == 0)
    {
      char *tmpbuf = (char *) xmalloc (sizeof ("0x12345678") + 1);
      unsigned long hash = strhash (dll_file_name);
      sprintf (tmpbuf, "0x%.8lX", 0x60000000|((hash<<16)&0xFFC0000));
      image_base_str = tmpbuf;
    }

  dyn_string_append_cstr (driver_cmdline, " -Wl,--image-base,");
  dyn_string_append_cstr (driver_cmdline, image_base_str);

  if (verbose)
    {
      dyn_string_append_cstr (driver_cmdline, " -v");
    }

  for (i = 1; i < argc; ++i)
    {
      if (driver_arg_indices[i])
	{
	  char *arg = saved_argv[i];
	  int quote = (strchr (arg, ' ') || strchr (arg, '\t'));
	  dyn_string_append_cstr (driver_cmdline,
	                     (quote) ? " \"" : " ");
	  dyn_string_append_cstr (driver_cmdline, arg);
	  dyn_string_append_cstr (driver_cmdline,
	                     (quote) ? "\"" : "");
	}
    }

  /* Step pre-1. If no --def <EXPORT_DEF> is specified,
     then create it and then pass it on.  */

  if (! def_file_seen)
    {
      int i;
      dyn_string_t step_pre1;

      step_pre1 = dyn_string_new (1024);

      dyn_string_append_cstr (step_pre1, dlltool_cmdline->s);
      if (export_all)
	{
	  dyn_string_append_cstr (step_pre1, " --export-all --exclude-symbol=");
	  dyn_string_append_cstr (step_pre1,
	  "_cygwin_dll_entry@12,DllMainCRTStartup@12,DllMain@12,DllEntryPoint@12");
	}
      dyn_string_append_cstr (step_pre1, " --output-def ");
      dyn_string_append_cstr (step_pre1, def_file_name);

      for (i = 1; i < argc; ++i)
	{
	  if (driver_arg_indices[i])
	    {
	      char *arg = saved_argv[i];
	      size_t len = strlen (arg);
	      if (len >= 2 && arg[len-2] == '.'
	          && (arg[len-1] == 'o' || arg[len-1] == 'a'))
		{
		  int quote = (strchr (arg, ' ') || strchr (arg, '\t'));
		  dyn_string_append_cstr (step_pre1,
				     (quote) ? " \"" : " ");
		  dyn_string_append_cstr (step_pre1, arg);
		  dyn_string_append_cstr (step_pre1,
				     (quote) ? "\"" : "");
		}
	    }
	}

      if (run (dlltool_name, step_pre1->s))
	cleanup_and_exit (1);

      dyn_string_delete (step_pre1);
    }

  dyn_string_append_cstr (dlltool_cmdline, " --def ");
  dyn_string_append_cstr (dlltool_cmdline, def_file_name);

  if (verbose)
    {
      fprintf (stderr, _("DLLTOOL name    : %s\n"), dlltool_name);
      fprintf (stderr, _("DLLTOOL options : %s\n"), dlltool_cmdline->s);
      fprintf (stderr, _("DRIVER name     : %s\n"), driver_name);
      fprintf (stderr, _("DRIVER options  : %s\n"), driver_cmdline->s);
    }

  /* Step 1. Call GCC/LD to create base relocation file. If using GCC, the
     driver command line will look like the following:
    
        % gcc -Wl,--dll --Wl,--base-file,foo.base [rest of command line]
    
     If the user does not specify a base name, create temporary one that
     is deleted at exit.  */

  if (! base_file_name)
    {
      char *fileprefix = choose_temp_base ();
      base_file_name = (char *) xmalloc (strlen (fileprefix) + 6);
      sprintf (base_file_name, "%s.base",
	       (dontdeltemps) ? mybasename (fileprefix) : fileprefix);
      delete_base_file = 1;
      free (fileprefix);
    }

  {
    int quote;

    dyn_string_t step1 = dyn_string_new (driver_cmdline->length
					 + strlen (base_file_name)
					 + 20);
    dyn_string_append_cstr (step1, "-Wl,--base-file,");
    quote = (strchr (base_file_name, ' ')
	     || strchr (base_file_name, '\t'));
    dyn_string_append_cstr (step1,
	               (quote) ? "\"" : "");
    dyn_string_append_cstr (step1, base_file_name);
    dyn_string_append_cstr (step1,
	               (quote) ? "\"" : "");
    if (driver_cmdline->length)
      {
	dyn_string_append_cstr (step1, " ");
	dyn_string_append_cstr (step1, driver_cmdline->s);
      }

    if (run (driver_name, step1->s))
      cleanup_and_exit (1);

    dyn_string_delete (step1);
  }

  /* Step 2. generate the exp file by running dlltool.
     dlltool command line will look like the following:
    
        % dlltool -Wl,--dll --Wl,--base-file,foo.base [rest of command line]
    
     If the user does not specify a base name, create temporary one that
     is deleted at exit.  */

  if (! exp_file_name)
    {
      char *p = strrchr (dll_name, '.');
      size_t prefix_len = (p) ? (size_t) (p - dll_name) : strlen (dll_name);

      exp_file_name = (char *) xmalloc (prefix_len + 4 + 1);
      strncpy (exp_file_name, dll_name, prefix_len);
      exp_file_name[prefix_len] = '\0';
      strcat (exp_file_name, ".exp");
      delete_exp_file = 1;
    }

  {
    int quote;

    dyn_string_t step2 = dyn_string_new (dlltool_cmdline->length
					 + strlen (base_file_name)
					 + strlen (exp_file_name)
				         + 20);

    dyn_string_append_cstr (step2, "--base-file ");
    quote = (strchr (base_file_name, ' ')
	     || strchr (base_file_name, '\t'));
    dyn_string_append_cstr (step2,
	               (quote) ? "\"" : "");
    dyn_string_append_cstr (step2, base_file_name);
    dyn_string_append_cstr (step2,
	               (quote) ? "\" " : " ");

    dyn_string_append_cstr (step2, "--output-exp ");
    quote = (strchr (exp_file_name, ' ')
	     || strchr (exp_file_name, '\t'));
    dyn_string_append_cstr (step2,
	               (quote) ? "\"" : "");
    dyn_string_append_cstr (step2, exp_file_name);
    dyn_string_append_cstr (step2,
	               (quote) ? "\"" : "");

    if (dlltool_cmdline->length)
      {
	dyn_string_append_cstr (step2, " ");
	dyn_string_append_cstr (step2, dlltool_cmdline->s);
      }

    if (run (dlltool_name, step2->s))
      cleanup_and_exit (1);

    dyn_string_delete (step2);
  }

  /*
   * Step 3. Call GCC/LD to again, adding the exp file this time.
   * driver command line will look like the following:
   *
   *    % gcc -Wl,--dll --Wl,--base-file,foo.base foo.exp [rest ...]
   */

  {
    int quote;

    dyn_string_t step3 = dyn_string_new (driver_cmdline->length
					 + strlen (exp_file_name)
					 + strlen (base_file_name)
				         + 20);
    dyn_string_append_cstr (step3, "-Wl,--base-file,");
    quote = (strchr (base_file_name, ' ')
	     || strchr (base_file_name, '\t'));
    dyn_string_append_cstr (step3,
	               (quote) ? "\"" : "");
    dyn_string_append_cstr (step3, base_file_name);
    dyn_string_append_cstr (step3,
	               (quote) ? "\" " : " ");

    quote = (strchr (exp_file_name, ' ')
	     || strchr (exp_file_name, '\t'));
    dyn_string_append_cstr (step3,
	               (quote) ? "\"" : "");
    dyn_string_append_cstr (step3, exp_file_name);
    dyn_string_append_cstr (step3,
	               (quote) ? "\"" : "");

    if (driver_cmdline->length)
      {
	dyn_string_append_cstr (step3, " ");
	dyn_string_append_cstr (step3, driver_cmdline->s);
      }

    if (run (driver_name, step3->s))
      cleanup_and_exit (1);

    dyn_string_delete (step3);
  }


  /*
   * Step 4. Run DLLTOOL again using the same command line.
   */

  {
    int quote;
    dyn_string_t step4 = dyn_string_new (dlltool_cmdline->length
					 + strlen (base_file_name)
					 + strlen (exp_file_name)
				         + 20);

    dyn_string_append_cstr (step4, "--base-file ");
    quote = (strchr (base_file_name, ' ')
	     || strchr (base_file_name, '\t'));
    dyn_string_append_cstr (step4,
	               (quote) ? "\"" : "");
    dyn_string_append_cstr (step4, base_file_name);
    dyn_string_append_cstr (step4,
	               (quote) ? "\" " : " ");

    dyn_string_append_cstr (step4, "--output-exp ");
    quote = (strchr (exp_file_name, ' ')
	     || strchr (exp_file_name, '\t'));
    dyn_string_append_cstr (step4,
	               (quote) ? "\"" : "");
    dyn_string_append_cstr (step4, exp_file_name);
    dyn_string_append_cstr (step4,
	               (quote) ? "\"" : "");

    if (dlltool_cmdline->length)
      {
	dyn_string_append_cstr (step4, " ");
	dyn_string_append_cstr (step4, dlltool_cmdline->s);
      }

    if (output_lib_file_name)
      {
	dyn_string_append_cstr (step4, " --output-lib ");
	dyn_string_append_cstr (step4, output_lib_file_name);
      }

    if (run (dlltool_name, step4->s))
      cleanup_and_exit (1);

    dyn_string_delete (step4);
  }


  /*
   * Step 5. Link it all together and be done with it.
   * driver command line will look like the following:
   *
   *    % gcc -Wl,--dll foo.exp [rest ...]
   *
   */

  {
    int quote;

    dyn_string_t step5 = dyn_string_new (driver_cmdline->length
					 + strlen (exp_file_name)
				         + 20);
    quote = (strchr (exp_file_name, ' ')
	     || strchr (exp_file_name, '\t'));
    dyn_string_append_cstr (step5,
	               (quote) ? "\"" : "");
    dyn_string_append_cstr (step5, exp_file_name);
    dyn_string_append_cstr (step5,
	               (quote) ? "\"" : "");

    if (driver_cmdline->length)
      {
	dyn_string_append_cstr (step5, " ");
	dyn_string_append_cstr (step5, driver_cmdline->s);
      }

    if (run (driver_name, step5->s))
      cleanup_and_exit (1);

    dyn_string_delete (step5);
  }

  cleanup_and_exit (0);

  return 0;
}