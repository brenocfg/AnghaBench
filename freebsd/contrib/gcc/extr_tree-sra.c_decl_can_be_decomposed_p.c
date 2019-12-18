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
 int TDF_DETAILS ; 
 scalar_t__ TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  is_gimple_non_addressable (int /*<<< orphan*/ ) ; 
 scalar_t__ is_sra_scalar_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sra_type_can_be_decomposed_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
decl_can_be_decomposed_p (tree var)
{
  /* Early out for scalars.  */
  if (is_sra_scalar_type (TREE_TYPE (var)))
    return false;

  /* The variable must not be aliased.  */
  if (!is_gimple_non_addressable (var))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "Cannot scalarize variable ");
	  print_generic_expr (dump_file, var, dump_flags);
	  fprintf (dump_file, " because it must live in memory\n");
	}
      return false;
    }

  /* The variable must not be volatile.  */
  if (TREE_THIS_VOLATILE (var))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "Cannot scalarize variable ");
	  print_generic_expr (dump_file, var, dump_flags);
	  fprintf (dump_file, " because it is declared volatile\n");
	}
      return false;
    }

  /* We must be able to decompose the variable's type.  */
  if (!sra_type_can_be_decomposed_p (TREE_TYPE (var)))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "Cannot scalarize variable ");
	  print_generic_expr (dump_file, var, dump_flags);
	  fprintf (dump_file, " because its type cannot be decomposed\n");
	}
      return false;
    }

  return true;
}