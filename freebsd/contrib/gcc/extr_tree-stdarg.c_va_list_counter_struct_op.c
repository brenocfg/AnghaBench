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
struct stdarg_info {int /*<<< orphan*/  va_list_vars; } ;

/* Variables and functions */
 scalar_t__ COMPONENT_REF ; 
 int /*<<< orphan*/  DECL_UID (scalar_t__) ; 
 scalar_t__ FIELD_DECL ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ SSA_NAME_VAR (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_base_address (scalar_t__) ; 
 int /*<<< orphan*/  va_list_counter_op (struct stdarg_info*,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ va_list_fpr_counter_field ; 
 scalar_t__ va_list_gpr_counter_field ; 

__attribute__((used)) static bool
va_list_counter_struct_op (struct stdarg_info *si, tree ap, tree var,
			   bool write_p)
{
  tree base;

  if (TREE_CODE (ap) != COMPONENT_REF
      || TREE_CODE (TREE_OPERAND (ap, 1)) != FIELD_DECL)
    return false;

  if (TREE_CODE (var) != SSA_NAME
      || bitmap_bit_p (si->va_list_vars, DECL_UID (SSA_NAME_VAR (var))))
    return false;

  base = get_base_address (ap);
  if (TREE_CODE (base) != VAR_DECL
      || !bitmap_bit_p (si->va_list_vars, DECL_UID (base)))
    return false;

  if (TREE_OPERAND (ap, 1) == va_list_gpr_counter_field)
    va_list_counter_op (si, ap, var, true, write_p);
  else if (TREE_OPERAND (ap, 1) == va_list_fpr_counter_field)
    va_list_counter_op (si, ap, var, false, write_p);

  return true;
}