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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  INTEGRAL_MODE_P (int) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  REPORT_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int UNITS_PER_SIMD_WORD ; 
 int /*<<< orphan*/  VECTOR_MODE_P (int) ; 
 int /*<<< orphan*/  build_vector_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_dump ; 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 

tree
get_vectype_for_scalar_type (tree scalar_type)
{
  enum machine_mode inner_mode = TYPE_MODE (scalar_type);
  int nbytes = GET_MODE_SIZE (inner_mode);
  int nunits;
  tree vectype;

  if (nbytes == 0 || nbytes >= UNITS_PER_SIMD_WORD)
    return NULL_TREE;

  /* FORNOW: Only a single vector size per target (UNITS_PER_SIMD_WORD)
     is expected.  */
  nunits = UNITS_PER_SIMD_WORD / nbytes;

  vectype = build_vector_type (scalar_type, nunits);
  if (vect_print_dump_info (REPORT_DETAILS))
    {
      fprintf (vect_dump, "get vectype with %d units of type ", nunits);
      print_generic_expr (vect_dump, scalar_type, TDF_SLIM);
    }

  if (!vectype)
    return NULL_TREE;

  if (vect_print_dump_info (REPORT_DETAILS))
    {
      fprintf (vect_dump, "vectype: ");
      print_generic_expr (vect_dump, vectype, TDF_SLIM);
    }

  if (!VECTOR_MODE_P (TYPE_MODE (vectype))
      && !INTEGRAL_MODE_P (TYPE_MODE (vectype)))
    {
      if (vect_print_dump_info (REPORT_DETAILS))
        fprintf (vect_dump, "mode not supported by target.");
      return NULL_TREE;
    }

  return vectype;
}