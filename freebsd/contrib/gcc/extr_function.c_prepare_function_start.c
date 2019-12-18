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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ DECL_STRUCT_FUNCTION (scalar_t__) ; 
 int /*<<< orphan*/  allocate_struct_function (scalar_t__) ; 
 scalar_t__ caller_save_needed ; 
 scalar_t__ cfun ; 
 int cse_not_expected ; 
 scalar_t__ frame_pointer_needed ; 
 int generating_concat_p ; 
 int /*<<< orphan*/  init_emit () ; 
 int /*<<< orphan*/  init_expr () ; 
 int /*<<< orphan*/  init_varasm_status (scalar_t__) ; 
 int /*<<< orphan*/  optimize ; 
 scalar_t__ reg_renumber ; 
 scalar_t__ virtuals_instantiated ; 

__attribute__((used)) static void
prepare_function_start (tree fndecl)
{
  if (fndecl && DECL_STRUCT_FUNCTION (fndecl))
    cfun = DECL_STRUCT_FUNCTION (fndecl);
  else
    allocate_struct_function (fndecl);
  init_emit ();
  init_varasm_status (cfun);
  init_expr ();

  cse_not_expected = ! optimize;

  /* Caller save not needed yet.  */
  caller_save_needed = 0;

  /* We haven't done register allocation yet.  */
  reg_renumber = 0;

  /* Indicate that we have not instantiated virtual registers yet.  */
  virtuals_instantiated = 0;

  /* Indicate that we want CONCATs now.  */
  generating_concat_p = 1;

  /* Indicate we have no need of a frame pointer yet.  */
  frame_pointer_needed = 0;
}