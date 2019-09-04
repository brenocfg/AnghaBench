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
struct iconv_hooks {int /*<<< orphan*/ * data; int /*<<< orphan*/ * wc_hook; int /*<<< orphan*/  uc_hook; int /*<<< orphan*/ * wc_to_mb_fallback; int /*<<< orphan*/ * mb_to_wc_fallback; int /*<<< orphan*/ * uc_to_mb_fallback; int /*<<< orphan*/ * mb_to_uc_fallback; } ;
struct iconv_fallbacks {int /*<<< orphan*/ * data; int /*<<< orphan*/ * wc_hook; int /*<<< orphan*/  uc_hook; int /*<<< orphan*/ * wc_to_mb_fallback; int /*<<< orphan*/ * mb_to_wc_fallback; int /*<<< orphan*/ * uc_to_mb_fallback; int /*<<< orphan*/ * mb_to_uc_fallback; } ;
typedef  scalar_t__ iconv_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  ICONV_SET_FALLBACKS ; 
 int /*<<< orphan*/  ICONV_SET_HOOKS ; 
 char* _ (char*) ; 
 void* check_subst_formatstring (char*,char*) ; 
 int /*<<< orphan*/  cjkcode ; 
 int convert (scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 int discard_unconvertible ; 
 int errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  iconv_canonicalize (char const*) ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char const*,char const*) ; 
 int /*<<< orphan*/  iconvctl (scalar_t__,int /*<<< orphan*/ ,struct iconv_hooks*) ; 
 int /*<<< orphan*/  iconvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* ilseq_byte_subst ; 
 char* ilseq_byte_subst_buffer ; 
 int ilseq_byte_subst_size ; 
 char* ilseq_unicode_subst ; 
 char* ilseq_unicode_subst_buffer ; 
 int ilseq_unicode_subst_size ; 
 char* ilseq_wchar_subst ; 
 void* ilseq_wchar_subst_size ; 
 int /*<<< orphan*/  is_cjk_encoding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_one ; 
 int /*<<< orphan*/  print_version () ; 
 char* program_name ; 
 int /*<<< orphan*/  set_program_name (char*) ; 
 int silent ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,size_t) ; 
 scalar_t__ subst_mb_to_mb_cd ; 
 char* subst_mb_to_mb_temp_buffer ; 
 scalar_t__ subst_mb_to_uc_cd ; 
 int /*<<< orphan*/ * subst_mb_to_uc_fallback ; 
 unsigned int* subst_mb_to_uc_temp_buffer ; 
 int /*<<< orphan*/ * subst_mb_to_wc_fallback ; 
 scalar_t__ subst_uc_to_mb_cd ; 
 int /*<<< orphan*/ * subst_uc_to_mb_fallback ; 
 char* subst_uc_to_mb_temp_buffer ; 
 int /*<<< orphan*/ * subst_wc_to_mb_fallback ; 
 int /*<<< orphan*/  textdomain (char*) ; 
 int /*<<< orphan*/  update_line_column ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ xmalloc (int) ; 

int main (int argc, char* argv[])
{
  const char* fromcode = NULL;
  const char* tocode = NULL;
  int do_list = 0;
  iconv_t cd;
  struct iconv_fallbacks fallbacks;
  struct iconv_hooks hooks;
  int i;
  int status;

  set_program_name (argv[0]);
#if HAVE_SETLOCALE
  /* Needed for the locale dependent encodings, "char" and "wchar_t",
     and for gettext. */
  setlocale(LC_CTYPE,"");
#if ENABLE_NLS
  /* Needed for gettext. */
  setlocale(LC_MESSAGES,"");
#endif
#endif
#if ENABLE_NLS
  bindtextdomain("libiconv",relocate(LOCALEDIR));
#endif
  textdomain("libiconv");
  for (i = 1; i < argc;) {
    size_t len = strlen(argv[i]);
    if (!strcmp(argv[i],"--")) {
      i++;
      break;
    }
    if (!strcmp(argv[i],"-f")
        /* --f ... --from-code */
        || (len >= 3 && len <= 11 && !strncmp(argv[i],"--from-code",len))
        /* --from-code=... */
        || (len >= 12 && !strncmp(argv[i],"--from-code=",12))) {
      if (len < 12)
        if (i == argc-1) usage(1);
      if (fromcode != NULL) usage(1);
      if (len < 12) {
        fromcode = argv[i+1];
        i += 2;
      } else {
        fromcode = argv[i]+12;
        i++;
      }
      continue;
    }
    if (!strcmp(argv[i],"-t")
        /* --t ... --to-code */
        || (len >= 3 && len <= 9 && !strncmp(argv[i],"--to-code",len))
        /* --from-code=... */
        || (len >= 10 && !strncmp(argv[i],"--to-code=",10))) {
      if (len < 10)
        if (i == argc-1) usage(1);
      if (tocode != NULL) usage(1);
      if (len < 10) {
        tocode = argv[i+1];
        i += 2;
      } else {
        tocode = argv[i]+10;
        i++;
      }
      continue;
    }
    if (!strcmp(argv[i],"-l")
        /* --l ... --list */
        || (len >= 3 && len <= 6 && !strncmp(argv[i],"--list",len))) {
      do_list = 1;
      i++;
      continue;
    }
    if (/* --by ... --byte-subst */
        (len >= 4 && len <= 12 && !strncmp(argv[i],"--byte-subst",len))
        /* --byte-subst=... */
        || (len >= 13 && !strncmp(argv[i],"--byte-subst=",13))) {
      if (len < 13) {
        if (i == argc-1) usage(1);
        ilseq_byte_subst = argv[i+1];
        i += 2;
      } else {
        ilseq_byte_subst = argv[i]+13;
        i++;
      }
      ilseq_byte_subst_size =
        check_subst_formatstring(ilseq_byte_subst, "--byte-subst");
      continue;
    }
    if (/* --w ... --widechar-subst */
        (len >= 3 && len <= 16 && !strncmp(argv[i],"--widechar-subst",len))
        /* --widechar-subst=... */
        || (len >= 17 && !strncmp(argv[i],"--widechar-subst=",17))) {
      if (len < 17) {
        if (i == argc-1) usage(1);
        ilseq_wchar_subst = argv[i+1];
        i += 2;
      } else {
        ilseq_wchar_subst = argv[i]+17;
        i++;
      }
      ilseq_wchar_subst_size =
        check_subst_formatstring(ilseq_wchar_subst, "--widechar-subst");
      continue;
    }
    if (/* --u ... --unicode-subst */
        (len >= 3 && len <= 15 && !strncmp(argv[i],"--unicode-subst",len))
        /* --unicode-subst=... */
        || (len >= 16 && !strncmp(argv[i],"--unicode-subst=",16))) {
      if (len < 16) {
        if (i == argc-1) usage(1);
        ilseq_unicode_subst = argv[i+1];
        i += 2;
      } else {
        ilseq_unicode_subst = argv[i]+16;
        i++;
      }
      ilseq_unicode_subst_size =
        check_subst_formatstring(ilseq_unicode_subst, "--unicode-subst");
      continue;
    }
    if /* --s ... --silent */
       (len >= 3 && len <= 8 && !strncmp(argv[i],"--silent",len)) {
      silent = 1;
      i++;
      continue;
    }
    if /* --h ... --help */
       (len >= 3 && len <= 6 && !strncmp(argv[i],"--help",len)) {
      usage(0);
    }
    if /* --v ... --version */
       (len >= 3 && len <= 9 && !strncmp(argv[i],"--version",len)) {
      print_version();
    }
#if O_BINARY
    /* Backward compatibility with iconv <= 1.9.1. */
    if /* --bi ... --binary */
       (len >= 4 && len <= 8 && !strncmp(argv[i],"--binary",len)) {
      i++;
      continue;
    }
#endif
    if (argv[i][0] == '-') {
      const char *option = argv[i] + 1;
      if (*option == '\0')
        usage(1);
      for (; *option; option++)
        switch (*option) {
          case 'c': discard_unconvertible = 1; break;
          case 's': silent = 1; break;
          default: usage(1);
        }
      i++;
      continue;
    }
    break;
  }
  if (do_list) {
    if (i != 2 || i != argc)
      usage(1);
    iconvlist(print_one,NULL);
    status = 0;
  } else {
#if O_BINARY
    SET_BINARY(fileno(stdout));
#endif
    if (fromcode == NULL)
      fromcode = "char";
    if (tocode == NULL)
      tocode = "char";
    cd = iconv_open(tocode,fromcode);
    if (cd == (iconv_t)(-1)) {
      if (iconv_open("UCS-4",fromcode) == (iconv_t)(-1))
        error(0,0,
              /* TRANSLATORS: An error message.
                 The placeholder expands to the encoding name, specified through --from-code.  */
              _("conversion from %s unsupported"),
              fromcode);
      else if (iconv_open(tocode,"UCS-4") == (iconv_t)(-1))
        error(0,0,
              /* TRANSLATORS: An error message.
                 The placeholder expands to the encoding name, specified through --to-code.  */
              _("conversion to %s unsupported"),
              tocode);
      else
        error(0,0,
              /* TRANSLATORS: An error message.
                 The placeholders expand to the encoding names, specified through --from-code and --to-code, respectively.  */
              _("conversion from %s to %s unsupported"),
              fromcode,tocode);
      error(EXIT_FAILURE,0,
            /* TRANSLATORS: Additional advice after an error message.
               The %s placeholder expands to the program name.  */
            _("try '%s -l' to get the list of supported encodings"),
            program_name);
    }
    /* Look at fromcode and tocode, to determine whether character widths
       should be determined according to legacy CJK conventions. */
    cjkcode = iconv_canonicalize(tocode);
    if (!is_cjk_encoding(cjkcode))
      cjkcode = iconv_canonicalize(fromcode);
    /* Set up fallback routines for handling impossible conversions. */
    if (ilseq_byte_subst != NULL)
      ilseq_byte_subst_buffer = (char*)xmalloc((ilseq_byte_subst_size+1)*sizeof(char));
    if (!discard_unconvertible) {
      #if HAVE_WCHAR_T
      if (ilseq_wchar_subst != NULL)
        ilseq_wchar_subst_buffer = (char*)xmalloc((ilseq_wchar_subst_size+1)*sizeof(char));
      #endif
      if (ilseq_unicode_subst != NULL)
        ilseq_unicode_subst_buffer = (char*)xmalloc((ilseq_unicode_subst_size+1)*sizeof(char));
      if (ilseq_byte_subst != NULL) {
        subst_mb_to_uc_cd = iconv_open("UCS-4-INTERNAL","char");
        subst_mb_to_uc_temp_buffer = (unsigned int*)xmalloc(ilseq_byte_subst_size*sizeof(unsigned int));
        #if HAVE_WCHAR_T
        subst_mb_to_wc_cd = iconv_open("wchar_t","char");
        subst_mb_to_wc_temp_buffer = (wchar_t*)xmalloc(ilseq_byte_subst_size*sizeof(wchar_t));
        #endif
        subst_mb_to_mb_cd = iconv_open(tocode,"char");
        subst_mb_to_mb_temp_buffer = (char*)xmalloc(ilseq_byte_subst_size*4);
      }
      #if HAVE_WCHAR_T
      if (ilseq_wchar_subst != NULL) {
        subst_wc_to_mb_cd = iconv_open(tocode,"char");
        subst_wc_to_mb_temp_buffer = (char*)xmalloc(ilseq_wchar_subst_size*4);
      }
      #endif
      if (ilseq_unicode_subst != NULL) {
        subst_uc_to_mb_cd = iconv_open(tocode,"char");
        subst_uc_to_mb_temp_buffer = (char*)xmalloc(ilseq_unicode_subst_size*4);
      }
      fallbacks.mb_to_uc_fallback =
        (ilseq_byte_subst != NULL ? subst_mb_to_uc_fallback : NULL);
      fallbacks.uc_to_mb_fallback =
        (ilseq_unicode_subst != NULL ? subst_uc_to_mb_fallback : NULL);
      fallbacks.mb_to_wc_fallback =
        (ilseq_byte_subst != NULL ? subst_mb_to_wc_fallback : NULL);
      fallbacks.wc_to_mb_fallback =
        (ilseq_wchar_subst != NULL ? subst_wc_to_mb_fallback : NULL);
      fallbacks.data = NULL;
      iconvctl(cd, ICONV_SET_FALLBACKS, &fallbacks);
    }
    /* Set up hooks for updating the line and column position. */
    hooks.uc_hook = update_line_column;
    hooks.wc_hook = NULL;
    hooks.data = NULL;
    iconvctl(cd, ICONV_SET_HOOKS, &hooks);
    if (i == argc)
      status = convert(cd,fileno(stdin),
                       /* TRANSLATORS: A filename substitute denoting standard input.  */
                       _("(stdin)"));
    else {
      status = 0;
      for (; i < argc; i++) {
        const char* infilename = argv[i];
        FILE* infile = fopen(infilename,"r");
        if (infile == NULL) {
          int saved_errno = errno;
          error(0,saved_errno,
                /* TRANSLATORS: The first part of an error message.
                   It is followed by a colon and a detail message.
                   The %s placeholder expands to the input file name.  */
                _("%s"),
                infilename);
          status = 1;
        } else {
          status |= convert(cd,fileno(infile),infilename);
          fclose(infile);
        }
      }
    }
    iconv_close(cd);
  }
  if (ferror(stdout) || fclose(stdout)) {
    error(0,0,
          /* TRANSLATORS: An error message.  */
          _("I/O error"));
    status = 1;
  }
  exit(status);
}