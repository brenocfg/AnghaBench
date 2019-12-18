#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_3__ {int /*<<< orphan*/  (* destructor ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* constructor ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; scalar_t__ have_ctors_dtors; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_mark_needed_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_or_defer_fn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_function (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_syntax_only ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void
finish_objects (int method_type, int initp, tree body)
{
  tree fn;

  /* Finish up.  */
  finish_compound_stmt (body);
  fn = finish_function (0);
  expand_or_defer_fn (fn);

  /* When only doing semantic analysis, and no RTL generation, we
     can't call functions that directly emit assembly code; there is
     no assembly file in which to put the code.  */
  if (flag_syntax_only)
    return;

  if (targetm.have_ctors_dtors)
    {
      rtx fnsym = XEXP (DECL_RTL (fn), 0);
      cgraph_mark_needed_node (cgraph_node (fn));
      if (method_type == 'I')
	(* targetm.asm_out.constructor) (fnsym, initp);
      else
	(* targetm.asm_out.destructor) (fnsym, initp);
    }
}