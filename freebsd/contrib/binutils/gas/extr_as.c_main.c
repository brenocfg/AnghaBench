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
typedef  int /*<<< orphan*/  symbolS ;
struct defsym_list {struct defsym_list* next; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  segT ;

/* Variables and functions */
 int /*<<< orphan*/  END_PROGRESS (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  HOST_SPECIAL_INIT (int,char**) ; 
 scalar_t__ IS_ELF ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  OBJ_DEFAULT_OUTPUT_FILE_NAME ; 
 scalar_t__ OUTPUT_FLAVOR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  PROGRESS (int) ; 
 int SEC_CODE ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  START_PROGRESS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_SET_VOLATILE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  absolute_section ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bfd_init () ; 
 int /*<<< orphan*/  bfd_set_error_program_name (char*) ; 
 int /*<<< orphan*/  bfd_set_section_flags (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfi_finish () ; 
 int chunksize ; 
 int /*<<< orphan*/  close_output_file ; 
 int /*<<< orphan*/  cond_finish_check (int) ; 
 int /*<<< orphan*/  create_obj_attrs_section () ; 
 scalar_t__ debug_memory ; 
 struct defsym_list* defsyms ; 
 int /*<<< orphan*/  dump_statistics ; 
 int /*<<< orphan*/  dwarf2_finish () ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  expr_begin () ; 
 scalar_t__ flag_always_generate_output ; 
 scalar_t__ flag_execstack ; 
 scalar_t__ flag_fatal_warnings ; 
 int /*<<< orphan*/  flag_macro_alternate ; 
 int flag_mri ; 
 scalar_t__ flag_noexecstack ; 
 scalar_t__ flag_print_statistics ; 
 int /*<<< orphan*/  frag_init () ; 
 int /*<<< orphan*/  free (struct defsym_list*) ; 
 int /*<<< orphan*/  get_run_time () ; 
 scalar_t__ had_errors () ; 
 scalar_t__ had_warnings () ; 
 int /*<<< orphan*/  hex_init () ; 
 int /*<<< orphan*/  input_scrub_begin () ; 
 int /*<<< orphan*/  input_scrub_end () ; 
 int /*<<< orphan*/  itbl_init () ; 
 int /*<<< orphan*/  listing_filename ; 
 int /*<<< orphan*/  listing_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macro_expr ; 
 int /*<<< orphan*/  macro_init (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_end () ; 
 char* myname ; 
 int /*<<< orphan*/  out_file_name ; 
 int /*<<< orphan*/  output_file_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_args (int*,char***) ; 
 int /*<<< orphan*/  perform_an_assembly_pass (int,char**) ; 
 int /*<<< orphan*/  print_dependencies () ; 
 int /*<<< orphan*/  read_begin () ; 
 scalar_t__ seen_at_least_1_file () ; 
 int /*<<< orphan*/  select_emulation_mode (int,char**) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  start_time ; 
 scalar_t__ stdoutput ; 
 int /*<<< orphan*/  subseg_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subsegs_begin () ; 
 int /*<<< orphan*/  subsegs_finish () ; 
 int /*<<< orphan*/  symbol_begin () ; 
 int /*<<< orphan*/ * symbol_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_table_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_init_after_args () ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_if_ordinary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_object_file () ; 
 int /*<<< orphan*/  xatexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 
 int /*<<< orphan*/  zero_address_frag ; 

int
main (int argc, char ** argv)
{
  int macro_strip_at;
  int keep_it;

  start_time = get_run_time ();

#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
#if defined (HAVE_SETLOCALE)
  setlocale (LC_CTYPE, "");
#endif
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  if (debug_memory)
    chunksize = 64;

#ifdef HOST_SPECIAL_INIT
  HOST_SPECIAL_INIT (argc, argv);
#endif

  myname = argv[0];
  xmalloc_set_program_name (myname);

  expandargv (&argc, &argv);

  START_PROGRESS (myname, 0);

#ifndef OBJ_DEFAULT_OUTPUT_FILE_NAME
#define OBJ_DEFAULT_OUTPUT_FILE_NAME "a.out"
#endif

  out_file_name = OBJ_DEFAULT_OUTPUT_FILE_NAME;

  hex_init ();
  bfd_init ();
  bfd_set_error_program_name (myname);

#ifdef USE_EMULATIONS
  select_emulation_mode (argc, argv);
#endif

  PROGRESS (1);
  /* Call parse_args before any of the init/begin functions
     so that switches like --hash-size can be honored.  */
  parse_args (&argc, &argv);
  symbol_begin ();
  frag_init ();
  subsegs_begin ();
  read_begin ();
  input_scrub_begin ();
  expr_begin ();

#ifndef OBJ_VMS /* Does its own file handling.  */
  /* It has to be called after dump_statistics ().  */
  xatexit (close_output_file);
#endif

  if (flag_print_statistics)
    xatexit (dump_statistics);

  macro_strip_at = 0;
#ifdef TC_I960
  macro_strip_at = flag_mri;
#endif

  macro_init (flag_macro_alternate, flag_mri, macro_strip_at, macro_expr);

  PROGRESS (1);

  output_file_create (out_file_name);
  assert (stdoutput != 0);

#ifdef tc_init_after_args
  tc_init_after_args ();
#endif

  itbl_init ();

  /* Now that we have fully initialized, and have created the output
     file, define any symbols requested by --defsym command line
     arguments.  */
  while (defsyms != NULL)
    {
      symbolS *sym;
      struct defsym_list *next;

      sym = symbol_new (defsyms->name, absolute_section, defsyms->value,
			&zero_address_frag);
      /* Make symbols defined on the command line volatile, so that they
	 can be redefined inside a source file.  This makes this assembler's
	 behaviour compatible with earlier versions, but it may not be
	 completely intuitive.  */
      S_SET_VOLATILE (sym);
      symbol_table_insert (sym);
      next = defsyms->next;
      free (defsyms);
      defsyms = next;
    }

  PROGRESS (1);

  /* Assemble it.  */
  perform_an_assembly_pass (argc, argv);

  cond_finish_check (-1);

#ifdef md_end
  md_end ();
#endif

#ifdef OBJ_ELF
  if (IS_ELF)
    create_obj_attrs_section ();
#endif

#if defined OBJ_ELF || defined OBJ_MAYBE_ELF
  if ((flag_execstack || flag_noexecstack)
      && OUTPUT_FLAVOR == bfd_target_elf_flavour)
    {
      segT gnustack;

      gnustack = subseg_new (".note.GNU-stack", 0);
      bfd_set_section_flags (stdoutput, gnustack,
			     SEC_READONLY | (flag_execstack ? SEC_CODE : 0));
                                                                             
    }
#endif

  /* If we've been collecting dwarf2 .debug_line info, either for
     assembly debugging or on behalf of the compiler, emit it now.  */
  dwarf2_finish ();

  /* If we constructed dwarf2 .eh_frame info, either via .cfi 
     directives from the user or by the backend, emit it now.  */
  cfi_finish ();

  if (seen_at_least_1_file ()
      && (flag_always_generate_output || had_errors () == 0))
    keep_it = 1;
  else
    keep_it = 0;

  /* This used to be done at the start of write_object_file in
     write.c, but that caused problems when doing listings when
     keep_it was zero.  This could probably be moved above md_end, but
     I didn't want to risk the change.  */
  subsegs_finish ();

  if (keep_it)
    write_object_file ();

#ifndef NO_LISTING
  listing_print (listing_filename);
#endif

  if (flag_fatal_warnings && had_warnings () > 0 && had_errors () == 0)
    as_bad (_("%d warnings, treating warnings as errors"), had_warnings ());

  if (had_errors () > 0 && ! flag_always_generate_output)
    keep_it = 0;

  if (!keep_it)
    unlink_if_ordinary (out_file_name);

  input_scrub_end ();

  END_PROGRESS (myname);

  /* Use xexit instead of return, because under VMS environments they
     may not place the same interpretation on the value given.  */
  if (had_errors () > 0)
    xexit (EXIT_FAILURE);

  /* Only generate dependency file if assembler was successful.  */
  print_dependencies ();

  xexit (EXIT_SUCCESS);
}