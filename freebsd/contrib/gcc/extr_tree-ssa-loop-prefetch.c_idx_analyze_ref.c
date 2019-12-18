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
struct ar_data {int* step; int* delta; int /*<<< orphan*/  stmt; int /*<<< orphan*/  loop; } ;
struct TYPE_3__ {int /*<<< orphan*/  step; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ affine_iv ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ ALIGN_INDIRECT_REF ; 
 scalar_t__ ARRAY_REF ; 
 scalar_t__ MISALIGNED_INDIRECT_REF ; 
 scalar_t__ PLUS_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_ref_element_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cst_and_fits_in_hwi (int /*<<< orphan*/ ) ; 
 int int_cst_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_iv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ zero_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
idx_analyze_ref (tree base, tree *index, void *data)
{
  struct ar_data *ar_data = data;
  tree ibase, step, stepsize;
  HOST_WIDE_INT istep, idelta = 0, imult = 1;
  affine_iv iv;

  if (TREE_CODE (base) == MISALIGNED_INDIRECT_REF
      || TREE_CODE (base) == ALIGN_INDIRECT_REF)
    return false;

  if (!simple_iv (ar_data->loop, ar_data->stmt, *index, &iv, false))
    return false;
  ibase = iv.base;
  step = iv.step;

  if (zero_p (step))
    istep = 0;
  else
    {
      if (!cst_and_fits_in_hwi (step))
	return false;
      istep = int_cst_value (step);
    }

  if (TREE_CODE (ibase) == PLUS_EXPR
      && cst_and_fits_in_hwi (TREE_OPERAND (ibase, 1)))
    {
      idelta = int_cst_value (TREE_OPERAND (ibase, 1));
      ibase = TREE_OPERAND (ibase, 0);
    }
  if (cst_and_fits_in_hwi (ibase))
    {
      idelta += int_cst_value (ibase);
      ibase = build_int_cst (TREE_TYPE (ibase), 0);
    }

  if (TREE_CODE (base) == ARRAY_REF)
    {
      stepsize = array_ref_element_size (base);
      if (!cst_and_fits_in_hwi (stepsize))
	return false;
      imult = int_cst_value (stepsize);

      istep *= imult;
      idelta *= imult;
    }

  *ar_data->step += istep;
  *ar_data->delta += idelta;
  *index = ibase;

  return true;
}