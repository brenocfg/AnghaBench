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
typedef  scalar_t__ tree ;
typedef  scalar_t__ rtx ;
struct TYPE_2__ {int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RTL (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  LOG_LINKS (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 int /*<<< orphan*/  REG_NOTES (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 TYPE_1__* cfun ; 
 int /*<<< orphan*/  reset_used_decls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_used_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_slot_list ; 
 int /*<<< orphan*/  unshare_all_rtl_1 (int /*<<< orphan*/ ,scalar_t__) ; 

void
unshare_all_rtl_again (rtx insn)
{
  rtx p;
  tree decl;

  for (p = insn; p; p = NEXT_INSN (p))
    if (INSN_P (p))
      {
	reset_used_flags (PATTERN (p));
	reset_used_flags (REG_NOTES (p));
	reset_used_flags (LOG_LINKS (p));
      }

  /* Make sure that virtual stack slots are not shared.  */
  reset_used_decls (DECL_INITIAL (cfun->decl));

  /* Make sure that virtual parameters are not shared.  */
  for (decl = DECL_ARGUMENTS (cfun->decl); decl; decl = TREE_CHAIN (decl))
    reset_used_flags (DECL_RTL (decl));

  reset_used_flags (stack_slot_list);

  unshare_all_rtl_1 (cfun->decl, insn);
}