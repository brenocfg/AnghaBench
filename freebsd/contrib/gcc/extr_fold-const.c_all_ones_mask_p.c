#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int /*<<< orphan*/  (* signed_type ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSHIFT_EXPR ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 unsigned int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  const_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_fit_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  size_int (unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
all_ones_mask_p (tree mask, int size)
{
  tree type = TREE_TYPE (mask);
  unsigned int precision = TYPE_PRECISION (type);
  tree tmask;

  tmask = build_int_cst (lang_hooks.types.signed_type (type), -1);
  tmask = force_fit_type (tmask, 0, false, false);

  return
    tree_int_cst_equal (mask,
			const_binop (RSHIFT_EXPR,
				     const_binop (LSHIFT_EXPR, tmask,
						  size_int (precision - size),
						  0),
				     size_int (precision - size), 0));
}