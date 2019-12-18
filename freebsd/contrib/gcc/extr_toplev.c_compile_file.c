#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* finish ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* final_write_globals ) () ;} ;
struct TYPE_9__ {TYPE_2__ decls; int /*<<< orphan*/  (* clear_binding_stack ) () ;int /*<<< orphan*/  (* parse_file ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* file_end ) () ;} ;
struct TYPE_8__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 char* IDENT_ASM_OP ; 
 int /*<<< orphan*/  TV_PARSE ; 
 int /*<<< orphan*/  TV_SYMOUT ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  aux_base_name ; 
 int /*<<< orphan*/  cgraph_varpool_assemble_pending_decls () ; 
 int /*<<< orphan*/  coverage_finish () ; 
 int /*<<< orphan*/  coverage_init (int /*<<< orphan*/ ) ; 
 TYPE_5__* debug_hooks ; 
 int /*<<< orphan*/  dw2_output_indirect_constants () ; 
 scalar_t__ dwarf2out_do_frame () ; 
 int /*<<< orphan*/  dwarf2out_frame_finish () ; 
 scalar_t__ errorcount ; 
 int /*<<< orphan*/  finish_aliases_2 () ; 
 scalar_t__ flag_mudflap ; 
 int /*<<< orphan*/  flag_no_ident ; 
 scalar_t__ flag_syntax_only ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  init_cgraph () ; 
 int /*<<< orphan*/  init_final (int /*<<< orphan*/ ) ; 
 TYPE_4__ lang_hooks ; 
 int /*<<< orphan*/  main_input_filename ; 
 int /*<<< orphan*/  mudflap_finish_file () ; 
 int /*<<< orphan*/  output_object_blocks () ; 
 int /*<<< orphan*/  output_shared_constant_pool () ; 
 int /*<<< orphan*/  process_pending_assemble_externals () ; 
 int /*<<< orphan*/  set_yydebug ; 
 scalar_t__ sorrycount ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 () ; 
 TYPE_3__ targetm ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 char* version_string ; 
 int /*<<< orphan*/  weak_finish () ; 

__attribute__((used)) static void
compile_file (void)
{
  /* Initialize yet another pass.  */

  init_cgraph ();
  init_final (main_input_filename);
  coverage_init (aux_base_name);

  timevar_push (TV_PARSE);

  /* Call the parser, which parses the entire file (calling
     rest_of_compilation for each function).  */
  lang_hooks.parse_file (set_yydebug);

  /* In case there were missing block closers,
     get us back to the global binding level.  */
  lang_hooks.clear_binding_stack ();

  /* Compilation is now finished except for writing
     what's left of the symbol table output.  */
  timevar_pop (TV_PARSE);

  if (flag_syntax_only || errorcount || sorrycount)
    return;

  lang_hooks.decls.final_write_globals ();
  cgraph_varpool_assemble_pending_decls ();
  finish_aliases_2 ();

  /* This must occur after the loop to output deferred functions.
     Else the coverage initializer would not be emitted if all the
     functions in this compilation unit were deferred.  */
  coverage_finish ();

  /* Likewise for mudflap static object registrations.  */
  if (flag_mudflap)
    mudflap_finish_file ();

  output_shared_constant_pool ();
  output_object_blocks ();

  /* Write out any pending weak symbol declarations.  */

  weak_finish ();

  /* Do dbx symbols.  */
  timevar_push (TV_SYMOUT);

#if defined DWARF2_DEBUGGING_INFO || defined DWARF2_UNWIND_INFO
  if (dwarf2out_do_frame ())
    dwarf2out_frame_finish ();
#endif

  (*debug_hooks->finish) (main_input_filename);
  timevar_pop (TV_SYMOUT);

  /* Output some stuff at end of file if nec.  */

  dw2_output_indirect_constants ();

  /* Flush any pending external directives.  */
  process_pending_assemble_externals ();

  /* Attach a special .ident directive to the end of the file to identify
     the version of GCC which compiled this code.  The format of the .ident
     string is patterned after the ones produced by native SVR4 compilers.  */
#ifdef IDENT_ASM_OP
  if (!flag_no_ident)
    fprintf (asm_out_file, "%s\"GCC: (GNU) %s\"\n",
	     IDENT_ASM_OP, version_string);
#endif

  /* This must be at the end.  Some target ports emit end of file directives
     into the assembly file here, and hence we can not output anything to the
     assembly file after this point.  */
  targetm.asm_out.file_end ();
}