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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_update_ssa () ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ need_to_initialize_update_ssa_p ; 
 int need_to_update_vops_p ; 
 int /*<<< orphan*/  syms_to_rename ; 

void
mark_sym_for_renaming (tree sym)
{
  if (need_to_initialize_update_ssa_p)
    init_update_ssa ();

  bitmap_set_bit (syms_to_rename, DECL_UID (sym));

  if (!is_gimple_reg (sym))
    need_to_update_vops_p = true;
}