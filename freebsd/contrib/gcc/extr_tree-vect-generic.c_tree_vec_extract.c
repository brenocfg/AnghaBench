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
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_FIELD_REF ; 
 int /*<<< orphan*/  VIEW_CONVERT_EXPR ; 
 scalar_t__ gimplify_build1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gimplify_build3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline tree
tree_vec_extract (block_stmt_iterator *bsi, tree type,
		  tree t, tree bitsize, tree bitpos)
{
  if (bitpos)
    return gimplify_build3 (bsi, BIT_FIELD_REF, type, t, bitsize, bitpos);
  else
    return gimplify_build1 (bsi, VIEW_CONVERT_EXPR, type, t);
}