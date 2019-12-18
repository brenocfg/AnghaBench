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
typedef  void* tree ;
struct loop {int dummy; } ;
struct iv {void* step; void* base; } ;
struct ifs_ivopts_data {void** step_p; int /*<<< orphan*/  stmt; TYPE_1__* ivopts_data; } ;
struct TYPE_2__ {struct loop* current_loop; } ;

/* Variables and functions */
 scalar_t__ ALIGN_INDIRECT_REF ; 
 scalar_t__ ARRAY_REF ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ MISALIGNED_INDIRECT_REF ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (void*) ; 
 void* array_ref_element_size (void*) ; 
 void* array_ref_low_bound (void*) ; 
 void* build_int_cst (int /*<<< orphan*/ ,int) ; 
 void* component_ref_field_offset (void*) ; 
 int /*<<< orphan*/  convert_affine_scev (struct loop*,int /*<<< orphan*/ ,void**,void**,int /*<<< orphan*/ ,int) ; 
 int expr_invariant_in_loop_p (struct loop*,void*) ; 
 void* fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 struct iv* get_iv (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  sizetype ; 

__attribute__((used)) static bool
idx_find_step (tree base, tree *idx, void *data)
{
  struct ifs_ivopts_data *dta = data;
  struct iv *iv;
  tree step, iv_base, iv_step, lbound, off;
  struct loop *loop = dta->ivopts_data->current_loop;

  if (TREE_CODE (base) == MISALIGNED_INDIRECT_REF
      || TREE_CODE (base) == ALIGN_INDIRECT_REF)
    return false;

  /* If base is a component ref, require that the offset of the reference
     be invariant.  */
  if (TREE_CODE (base) == COMPONENT_REF)
    {
      off = component_ref_field_offset (base);
      return expr_invariant_in_loop_p (loop, off);
    }

  /* If base is array, first check whether we will be able to move the
     reference out of the loop (in order to take its address in strength
     reduction).  In order for this to work we need both lower bound
     and step to be loop invariants.  */
  if (TREE_CODE (base) == ARRAY_REF)
    {
      step = array_ref_element_size (base);
      lbound = array_ref_low_bound (base);

      if (!expr_invariant_in_loop_p (loop, step)
	  || !expr_invariant_in_loop_p (loop, lbound))
	return false;
    }

  if (TREE_CODE (*idx) != SSA_NAME)
    return true;

  iv = get_iv (dta->ivopts_data, *idx);
  if (!iv)
    return false;

  /* XXX  We produce for a base of *D42 with iv->base being &x[0]
	  *&x[0], which is not folded and does not trigger the
	  ARRAY_REF path below.  */
  *idx = iv->base;

  if (!iv->step)
    return true;

  if (TREE_CODE (base) == ARRAY_REF)
    {
      step = array_ref_element_size (base);

      /* We only handle addresses whose step is an integer constant.  */
      if (TREE_CODE (step) != INTEGER_CST)
	return false;
    }
  else
    /* The step for pointer arithmetics already is 1 byte.  */
    step = build_int_cst (sizetype, 1);

  iv_base = iv->base;
  iv_step = iv->step;
  if (!convert_affine_scev (dta->ivopts_data->current_loop,
			    sizetype, &iv_base, &iv_step, dta->stmt,
			    false))
    {
      /* The index might wrap.  */
      return false;
    }

  step = fold_build2 (MULT_EXPR, sizetype, step, iv_step);

  if (!*dta->step_p)
    *dta->step_p = step;
  else
    *dta->step_p = fold_build2 (PLUS_EXPR, sizetype, *dta->step_p, step);

  return true;
}