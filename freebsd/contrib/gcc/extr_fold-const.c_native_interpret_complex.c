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
 int /*<<< orphan*/  build_complex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  native_interpret_expr (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static tree
native_interpret_complex (tree type, unsigned char *ptr, int len)
{
  tree etype, rpart, ipart;
  int size;

  etype = TREE_TYPE (type);
  size = GET_MODE_SIZE (TYPE_MODE (etype));
  if (size * 2 > len)
    return NULL_TREE;
  rpart = native_interpret_expr (etype, ptr, size);
  if (!rpart)
    return NULL_TREE;
  ipart = native_interpret_expr (etype, ptr+size, size);
  if (!ipart)
    return NULL_TREE;
  return build_complex (type, rpart, ipart);
}