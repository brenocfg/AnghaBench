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
 int /*<<< orphan*/  NOP_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_VECTOR_SUBPARTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
build_zero_vector (tree type)
{
  tree elem, list;
  int i, units;

  elem = fold_convert_const (NOP_EXPR, TREE_TYPE (type), integer_zero_node);
  units = TYPE_VECTOR_SUBPARTS (type);
  
  list = NULL_TREE;
  for (i = 0; i < units; i++)
    list = tree_cons (NULL_TREE, elem, list);
  return build_vector (type, list);
}