#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* ipa_reference_local_vars_info_t ;
struct TYPE_3__ {int /*<<< orphan*/  statics_read; int /*<<< orphan*/  statics_written; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ has_proper_scope_for_analysis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_statics_written ; 

__attribute__((used)) static void
check_operand (ipa_reference_local_vars_info_t local, 
	       tree t, bool checking_write)
{
  if (!t) return;

  if ((TREE_CODE (t) == VAR_DECL || TREE_CODE (t) == FUNCTION_DECL)
      && (has_proper_scope_for_analysis (t))) 
    {
      if (checking_write)
	{
	  if (local)
	    bitmap_set_bit (local->statics_written, DECL_UID (t));
	  /* Mark the write so we can tell which statics are
	     readonly.  */
	  bitmap_set_bit (module_statics_written, DECL_UID (t));
	}
      else if (local)
	bitmap_set_bit (local->statics_read, DECL_UID (t));
    }
}