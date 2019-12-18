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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 int /*<<< orphan*/  DECL_INITIAL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_RTL (scalar_t__) ; 
 int /*<<< orphan*/  SET_DECL_RTL (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  copy_rtx_if_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_slot_list ; 
 int /*<<< orphan*/  unshare_all_decls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unshare_all_rtl_in_chain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unshare_all_rtl_1 (tree fndecl, rtx insn)
{
  tree decl;

  /* Make sure that virtual parameters are not shared.  */
  for (decl = DECL_ARGUMENTS (fndecl); decl; decl = TREE_CHAIN (decl))
    SET_DECL_RTL (decl, copy_rtx_if_shared (DECL_RTL (decl)));

  /* Make sure that virtual stack slots are not shared.  */
  unshare_all_decls (DECL_INITIAL (fndecl));

  /* Unshare just about everything else.  */
  unshare_all_rtl_in_chain (insn);

  /* Make sure the addresses of stack slots found outside the insn chain
     (such as, in DECL_RTL of a variable) are not shared
     with the insn chain.

     This special care is necessary when the stack slot MEM does not
     actually appear in the insn chain.  If it does appear, its address
     is unshared from all else at that point.  */
  stack_slot_list = copy_rtx_if_shared (stack_slot_list);
}