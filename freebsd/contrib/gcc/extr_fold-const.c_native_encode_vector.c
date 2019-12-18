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

/* Variables and functions */
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TREE_VECTOR_CST_ELTS (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 int TYPE_VECTOR_SUBPARTS (scalar_t__) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int native_encode_expr (scalar_t__,unsigned char*,int) ; 

__attribute__((used)) static int
native_encode_vector (tree expr, unsigned char *ptr, int len)
{
  int i, size, offset, count;
  tree itype, elem, elements;

  offset = 0;
  elements = TREE_VECTOR_CST_ELTS (expr);
  count = TYPE_VECTOR_SUBPARTS (TREE_TYPE (expr));
  itype = TREE_TYPE (TREE_TYPE (expr));
  size = GET_MODE_SIZE (TYPE_MODE (itype));
  for (i = 0; i < count; i++)
    {
      if (elements)
	{
	  elem = TREE_VALUE (elements);
	  elements = TREE_CHAIN (elements);
	}
      else
	elem = NULL_TREE;

      if (elem)
	{
	  if (native_encode_expr (elem, ptr+offset, len-offset) != size)
	    return 0;
	}
      else
	{
	  if (offset + size > len)
	    return 0;
	  memset (ptr+offset, 0, size);
	}
      offset += size;
    }
  return offset;
}