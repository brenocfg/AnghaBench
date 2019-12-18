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
struct stat {int dummy; } ;
struct section_list {void* remove; } ;
typedef  void* bfd_boolean ;

/* Variables and functions */
 int EOF ; 
 void* FALSE ; 
 scalar_t__ LOCALS_ALL ; 
 scalar_t__ LOCALS_START_L ; 
 scalar_t__ LOCALS_UNDEF ; 
#define  OPTION_FORMATS_INFO 131 
#define  OPTION_KEEP_FILE_SYMBOLS 130 
#define  OPTION_ONLY_KEEP_DEBUG 129 
#define  OPTION_STRIP_UNNEEDED 128 
 scalar_t__ STRIP_ALL ; 
 scalar_t__ STRIP_DEBUG ; 
 scalar_t__ STRIP_NONDEBUG ; 
 scalar_t__ STRIP_UNDEF ; 
 scalar_t__ STRIP_UNNEEDED ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_specific_symbol (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  copy_file (char*,char*,char*,char*) ; 
 scalar_t__ discard_locals ; 
 int /*<<< orphan*/  display_info () ; 
 struct section_list* find_section_list (char*,void*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_file_size (char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int keep_file_symbols ; 
 int /*<<< orphan*/ * keep_specific_list ; 
 char* make_tempname (char*) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,char*) ; 
 char* optarg ; 
 int optind ; 
 void* preserve_dates ; 
 int /*<<< orphan*/  print_version (char*) ; 
 void* sections_removed ; 
 int /*<<< orphan*/  set_times (char*,struct stat*) ; 
 int /*<<< orphan*/  smart_rename (char*,char*,void*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int status ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strip_options ; 
 int /*<<< orphan*/ * strip_specific_list ; 
 scalar_t__ strip_symbols ; 
 int /*<<< orphan*/  strip_usage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlink_if_ordinary (char*) ; 
 void* verbose ; 
 void* wildcard ; 

__attribute__((used)) static int
strip_main (int argc, char *argv[])
{
  char *input_target = NULL;
  char *output_target = NULL;
  bfd_boolean show_version = FALSE;
  bfd_boolean formats_info = FALSE;
  int c;
  int i;
  struct section_list *p;
  char *output_file = NULL;

  while ((c = getopt_long (argc, argv, "I:O:F:K:N:R:o:sSpdgxXHhVvw",
			   strip_options, (int *) 0)) != EOF)
    {
      switch (c)
	{
	case 'I':
	  input_target = optarg;
	  break;
	case 'O':
	  output_target = optarg;
	  break;
	case 'F':
	  input_target = output_target = optarg;
	  break;
	case 'R':
	  p = find_section_list (optarg, TRUE);
	  p->remove = TRUE;
	  sections_removed = TRUE;
	  break;
	case 's':
	  strip_symbols = STRIP_ALL;
	  break;
	case 'S':
	case 'g':
	case 'd':	/* Historic BSD alias for -g.  Used by early NetBSD.  */
	  strip_symbols = STRIP_DEBUG;
	  break;
	case OPTION_STRIP_UNNEEDED:
	  strip_symbols = STRIP_UNNEEDED;
	  break;
	case 'K':
	  add_specific_symbol (optarg, &keep_specific_list);
	  break;
	case 'N':
	  add_specific_symbol (optarg, &strip_specific_list);
	  break;
	case 'o':
	  output_file = optarg;
	  break;
	case 'p':
	  preserve_dates = TRUE;
	  break;
	case 'x':
	  discard_locals = LOCALS_ALL;
	  break;
	case 'X':
	  discard_locals = LOCALS_START_L;
	  break;
	case 'v':
	  verbose = TRUE;
	  break;
	case 'V':
	  show_version = TRUE;
	  break;
	case OPTION_FORMATS_INFO:
	  formats_info = TRUE;
	  break;
	case OPTION_ONLY_KEEP_DEBUG:
	  strip_symbols = STRIP_NONDEBUG;
	  break;
	case OPTION_KEEP_FILE_SYMBOLS:
	  keep_file_symbols = 1;
	  break;
	case 0:
	  /* We've been given a long option.  */
	  break;
	case 'w':
	  wildcard = TRUE;
	  break;
	case 'H':
	case 'h':
	  strip_usage (stdout, 0);
	default:
	  strip_usage (stderr, 1);
	}
    }

  if (formats_info)
    {
      display_info ();
      return 0;
    }

  if (show_version)
    print_version ("strip");

  /* Default is to strip all symbols.  */
  if (strip_symbols == STRIP_UNDEF
      && discard_locals == LOCALS_UNDEF
      && strip_specific_list == NULL)
    strip_symbols = STRIP_ALL;

  if (output_target == NULL)
    output_target = input_target;

  i = optind;
  if (i == argc
      || (output_file != NULL && (i + 1) < argc))
    strip_usage (stderr, 1);

  for (; i < argc; i++)
    {
      int hold_status = status;
      struct stat statbuf;
      char *tmpname;

      if (get_file_size (argv[i]) < 1)
	{
	  status = 1;
	  continue;
	}

      if (preserve_dates)
	/* No need to check the return value of stat().
	   It has already been checked in get_file_size().  */
	stat (argv[i], &statbuf);

      if (output_file == NULL || strcmp (argv[i], output_file) == 0)
	tmpname = make_tempname (argv[i]);
      else
	tmpname = output_file;

      if (tmpname == NULL)
	{
	  non_fatal (_("could not create temporary file to hold stripped copy of '%s'"),
		     argv[i]);
	  status = 1;
	  continue;
	}

      status = 0;
      copy_file (argv[i], tmpname, input_target, output_target);
      if (status == 0)
	{
	  if (preserve_dates)
	    set_times (tmpname, &statbuf);
	  if (output_file != tmpname)
	    smart_rename (tmpname, output_file ? output_file : argv[i],
			  preserve_dates);
	  status = hold_status;
	}
      else
	unlink_if_ordinary (tmpname);
      if (output_file != tmpname)
	free (tmpname);
    }

  return status;
}