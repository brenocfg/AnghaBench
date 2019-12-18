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
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int TYPE_VECTOR_SUBPARTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  native_interpret_expr (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
native_interpret_vector (tree type, unsigned char *ptr, int len)
{
  tree etype, elem, elements;
  int i, size, count;

  etype = TREE_TYPE (type);
  size = GET_MODE_SIZE (TYPE_MODE (etype));
  count = TYPE_VECTOR_SUBPARTS (type);
  if (size * count > len)
    return NULL_TREE;

  elements = NULL_TREE;
  for (i = count - 1; i >= 0; i--)
    {
      elem = native_interpret_expr (etype, ptr+(i*size), size);
      if (!elem)
	return NULL_TREE;
      elements = tree_cons (NULL_TREE, elem, elements);
    }
  return build_vector (type, elements);
}