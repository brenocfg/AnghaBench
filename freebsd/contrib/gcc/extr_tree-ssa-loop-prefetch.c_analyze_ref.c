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
struct loop {int dummy; } ;
struct ar_data {int* step; int* delta; int /*<<< orphan*/  stmt; struct loop* loop; } ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 scalar_t__ COMPONENT_REF ; 
 int /*<<< orphan*/  DECL_FIELD_BIT_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NONADDRESSABLE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int for_each_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ar_data*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  idx_analyze_ref ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
analyze_ref (struct loop *loop, tree *ref_p, tree *base,
	     HOST_WIDE_INT *step, HOST_WIDE_INT *delta,
	     tree stmt)
{
  struct ar_data ar_data;
  tree off;
  HOST_WIDE_INT bit_offset;
  tree ref = *ref_p;

  *step = 0;
  *delta = 0;

  /* First strip off the component references.  Ignore bitfields.  */
  if (TREE_CODE (ref) == COMPONENT_REF
      && DECL_NONADDRESSABLE_P (TREE_OPERAND (ref, 1)))
    ref = TREE_OPERAND (ref, 0);

  *ref_p = ref;

  for (; TREE_CODE (ref) == COMPONENT_REF; ref = TREE_OPERAND (ref, 0))
    {
      off = DECL_FIELD_BIT_OFFSET (TREE_OPERAND (ref, 1));
      bit_offset = TREE_INT_CST_LOW (off);
      gcc_assert (bit_offset % BITS_PER_UNIT == 0);
      
      *delta += bit_offset / BITS_PER_UNIT;
    }

  *base = unshare_expr (ref);
  ar_data.loop = loop;
  ar_data.stmt = stmt;
  ar_data.step = step;
  ar_data.delta = delta;
  return for_each_index (base, idx_analyze_ref, &ar_data);
}