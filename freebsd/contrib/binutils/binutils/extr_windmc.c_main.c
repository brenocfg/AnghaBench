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
typedef  int /*<<< orphan*/  unichar ;
typedef  int /*<<< orphan*/  rc_uint_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CP_UTF16 ; 
 int EOF ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  bfd_init () ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* def_target_arch ; 
 int /*<<< orphan*/  do_sorts () ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fread (char*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  long_options ; 
 char* malloc (long) ; 
 int /*<<< orphan*/ * mc_create_path_text_file (int /*<<< orphan*/ *,char*) ; 
 char* mc_facility_codes ; 
 char* mc_nodes_lang ; 
 int /*<<< orphan*/  mc_set_content (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mc_set_inputfile (char*) ; 
 char* mc_severity_codes ; 
 int /*<<< orphan*/ * mc_unify_path (char*) ; 
 int mcset_automatic_null_termination ; 
 int mcset_bin_out_is_unicode ; 
 void* mcset_codepage_in ; 
 int mcset_codepage_out ; 
 int mcset_custom_bit ; 
 int /*<<< orphan*/ * mcset_dbg_dir ; 
 int /*<<< orphan*/ * mcset_header_dir ; 
 char* mcset_header_ext ; 
 void* mcset_max_message_length ; 
 char* mcset_mc_basename ; 
 int mcset_out_values_are_decimal ; 
 int mcset_prefix_bin ; 
 int /*<<< orphan*/ * mcset_rc_dir ; 
 int mcset_text_in_is_unicode ; 
 int mcset_use_hresult ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,long) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  print_version (char*) ; 
 int /*<<< orphan*/  probe_codepage (void**,int*,char*,int /*<<< orphan*/ ) ; 
 char* program_name ; 
 int /*<<< orphan*/  res_init () ; 
 int /*<<< orphan*/  set_default_bfd_target () ; 
 int /*<<< orphan*/  set_endianess (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char*) ; 
 void* strrchr (char*,char) ; 
 void* strtol (char*,char**,int) ; 
 scalar_t__ target_is_bigendian ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unicode_from_codepage (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,void*) ; 
 int /*<<< orphan*/  unicode_is_valid_codepage (int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_bin () ; 
 int /*<<< orphan*/  write_dbg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_rc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xexit (int /*<<< orphan*/ ) ; 
 char* xmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 
 char* xstrdup (char const*) ; 
 scalar_t__ yyparse () ; 

int
main (int argc, char **argv)
{
  FILE *h_fp;
  int c;
  char *target, *input_filename;
  int verbose;

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

  bfd_init ();
  set_default_bfd_target ();

  target = NULL;
  verbose = 0;
  input_filename = NULL;

  res_init ();

  while ((c = getopt_long (argc, argv, "C:F:O:h:e:m:r:x:aAbcdHunoUvV", long_options,
			   (int *) 0)) != EOF)
    {
      switch (c)
	{
	case 'b':
	  mcset_prefix_bin = 1;
	  break;
	case 'e':
	  {
	    mcset_header_ext = optarg;
	    if (mcset_header_ext[0] != '.' && mcset_header_ext[0] != 0)
	      {
		char *hsz = xmalloc (strlen (mcset_header_ext) + 2);

		sprintf (hsz, ".%s", mcset_header_ext);
		mcset_header_ext = hsz;
	      }
	  }
	  break;
	case 'h':
	  mcset_header_dir = mc_unify_path (optarg);
	  break;
	case 'r':
	  mcset_rc_dir = mc_unify_path (optarg);
	  break;
	case 'a':
	  mcset_text_in_is_unicode = 0;
	  break;
	case 'x':
	  if (*optarg != 0)
	    mcset_dbg_dir = mc_unify_path (optarg);
	  break;
	case 'A':
	  mcset_bin_out_is_unicode = 0;
	  break;
	case 'd':
	  mcset_out_values_are_decimal = 1;
	  break;
	case 'u':
	  mcset_text_in_is_unicode = 1;
	  break;
	case 'U':
	  mcset_bin_out_is_unicode = 1;
	  break;
	case 'c':
	  mcset_custom_bit = 1;
	  break;
	case 'n':
	  mcset_automatic_null_termination = 1;
	  break;
	case 'o':
	  mcset_use_hresult = 1;
	  fatal ("option -o is not implemented until yet.\n");
	  break;
	case 'F':
	  target = optarg;
	  break;
	case 'v':
	  verbose ++;
	  break;
	case 'm':
	  mcset_max_message_length = strtol (optarg, (char **) NULL, 10);
	  break;
	case 'C':
	  mcset_codepage_in = strtol (optarg, (char **) NULL, 10);
	  break;
	case 'O':
	  mcset_codepage_out = strtol (optarg, (char **) NULL, 10);
	  break;
	case '?':
	case 'H':
	  usage (stdout, 0);
	  break;
	case 'V':
	  print_version ("windmc");
	  break;

	default:
	  usage (stderr, 1);
	  break;
	}
    }
  if (input_filename == NULL && optind < argc)
    {
      input_filename = argv[optind];
      ++optind;
    }

  set_endianess (NULL, target);

  if (input_filename == NULL)
    {
      fprintf (stderr, "Error: No input file was specified.\n");
      usage (stderr, 1);
    }
  mc_set_inputfile (input_filename);

  if (!probe_codepage (&mcset_codepage_in, &mcset_text_in_is_unicode, "codepage_in", 0))
    usage (stderr, 1);
  if (mcset_codepage_out == 0)
    mcset_codepage_out = 1252;
  if (! unicode_is_valid_codepage (mcset_codepage_out))
    fatal ("Code page 0x%x is unknown.", (unsigned int) mcset_codepage_out);
  if (mcset_codepage_out == CP_UTF16)
    fatal ("UTF16 is no valid text output code page.");
  if (verbose)
    {
      fprintf (stderr, "// Default target is %s and it is %s endian.\n",
	def_target_arch, (target_is_bigendian ? "big" : "little"));
      fprintf (stderr, "// Input codepage: 0x%x\n", (unsigned int) mcset_codepage_in);
      fprintf (stderr, "// Output codepage: 0x%x\n", (unsigned int) mcset_codepage_out);
    }

  if (argc != optind)
    usage (stderr, 1);

  /* Initialize mcset_mc_basename.  */
  {
    const char *bn, *bn2;
    char *hsz;

    bn = strrchr (input_filename, '/');
    bn2 = strrchr (input_filename, '\\');
    if (! bn)
      bn = bn2;
    if (bn && bn2 && bn < bn2)
      bn = bn2;
    if (! bn)
      bn = input_filename;
    else
      bn++;
    mcset_mc_basename = hsz = xstrdup (bn);

    /* Cut of right-hand extension.  */
    if ((hsz = strrchr (hsz, '.')) != NULL)
      *hsz = 0;
  }

  /* Load the input file and do code page transformations to UTF16.  */
  {
    unichar *u;
    rc_uint_type ul;
    char *buff;
    long flen;
    FILE *fp = fopen (input_filename, "rb");

    if (!fp)
      fatal (_("unable to open file ,%s' for input.\n"), input_filename);

    fseek (fp, 0, SEEK_END);
    flen = ftell (fp);
    fseek (fp, 0, SEEK_SET);
    buff = malloc (flen + 3);
    memset (buff, 0, flen + 3);
    fread (buff, 1, flen, fp);
    fclose (fp);
    if (mcset_text_in_is_unicode != 1)
      {
	unicode_from_codepage (&ul, &u, buff, mcset_codepage_in);
	if (! u)
	  fatal ("Failed to convert input to UFT16\n");
	mc_set_content (u);
      }
    else
      {
	if ((flen & 1) != 0)
	  fatal (_("input file does not seems to be UFT16.\n"));
	mc_set_content ((unichar *) buff);
      }
    free (buff);
  }

  while (yyparse ())
    ;

  do_sorts ();

  h_fp = mc_create_path_text_file (mcset_header_dir, mcset_header_ext);
  write_header (h_fp);
  fclose (h_fp);

  h_fp = mc_create_path_text_file (mcset_rc_dir, ".rc");
  write_rc (h_fp);
  fclose (h_fp);

  if (mcset_dbg_dir != NULL)
    {
      h_fp = mc_create_path_text_file (mcset_dbg_dir, ".dbg");
      write_dbg (h_fp);
      fclose (h_fp);
    }
  write_bin ();

  if (mc_nodes_lang)
    free (mc_nodes_lang);
  if (mc_severity_codes)
    free (mc_severity_codes);
  if (mc_facility_codes)
    free (mc_facility_codes);

  xexit (0);
  return 0;
}