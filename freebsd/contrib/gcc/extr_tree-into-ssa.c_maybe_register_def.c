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
typedef  int /*<<< orphan*/  def_operand_p ;

/* Variables and functions */
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEF_FROM_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 scalar_t__ is_new_name (int /*<<< orphan*/ ) ; 
 scalar_t__ is_old_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_ssa_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  names_replaced_by (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_new_update_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_new_update_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ symbol_marked_for_renaming (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
maybe_register_def (def_operand_p def_p, tree stmt)
{
  tree def = DEF_FROM_PTR (def_p);
  tree sym = DECL_P (def) ? def : SSA_NAME_VAR (def);

  /* If DEF is a naked symbol that needs renaming, create a
     new name for it.  */
  if (symbol_marked_for_renaming (sym))
    {
      if (DECL_P (def))
	{
	  def = make_ssa_name (def, stmt);
	  SET_DEF (def_p, def);
	}

      register_new_update_single (def, sym);
    }
  else
    {
      /* If DEF is a new name, register it as a new definition
	 for all the names replaced by DEF.  */
      if (is_new_name (def))
	register_new_update_set (def, names_replaced_by (def));

      /* If DEF is an old name, register DEF as a new
	 definition for itself.  */
      if (is_old_name (def))
	register_new_update_single (def, def);
    }
}