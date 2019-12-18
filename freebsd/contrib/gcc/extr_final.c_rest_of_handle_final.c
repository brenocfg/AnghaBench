#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int /*<<< orphan*/  (* function_decl ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF ; 
 int /*<<< orphan*/  TV_SYMOUT ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_end_function (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  assemble_start_function (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  current_function_decl ; 
 TYPE_1__* debug_hooks ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  final (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  final_end_function () ; 
 int /*<<< orphan*/  final_start_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_basic_block_vars () ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  optimize ; 
 int /*<<< orphan*/  output_function_exception_table () ; 
 int /*<<< orphan*/  quiet_flag ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 int user_defined_section_attribute ; 

__attribute__((used)) static unsigned int
rest_of_handle_final (void)
{
  rtx x;
  const char *fnname;

  /* Get the function's name, as described by its RTL.  This may be
     different from the DECL_NAME name used in the source file.  */

  x = DECL_RTL (current_function_decl);
  gcc_assert (MEM_P (x));
  x = XEXP (x, 0);
  gcc_assert (GET_CODE (x) == SYMBOL_REF);
  fnname = XSTR (x, 0);

  assemble_start_function (current_function_decl, fnname);
  final_start_function (get_insns (), asm_out_file, optimize);
  final (get_insns (), asm_out_file, optimize);
  final_end_function ();

#ifdef TARGET_UNWIND_INFO
  /* ??? The IA-64 ".handlerdata" directive must be issued before
     the ".endp" directive that closes the procedure descriptor.  */
  output_function_exception_table ();
#endif

  assemble_end_function (current_function_decl, fnname);

#ifndef TARGET_UNWIND_INFO
  /* Otherwise, it feels unclean to switch sections in the middle.  */
  output_function_exception_table ();
#endif

  user_defined_section_attribute = false;

  if (! quiet_flag)
    fflush (asm_out_file);

  /* Release all memory allocated by flow.  */
  free_basic_block_vars ();

  /* Write DBX symbols if requested.  */

  /* Note that for those inline functions where we don't initially
     know for certain that we will be generating an out-of-line copy,
     the first invocation of this routine (rest_of_compilation) will
     skip over this code by doing a `goto exit_rest_of_compilation;'.
     Later on, wrapup_global_declarations will (indirectly) call
     rest_of_compilation again for those inline functions that need
     to have out-of-line copies generated.  During that call, we
     *will* be routed past here.  */

  timevar_push (TV_SYMOUT);
  (*debug_hooks->function_decl) (current_function_decl);
  timevar_pop (TV_SYMOUT);
  return 0;
}