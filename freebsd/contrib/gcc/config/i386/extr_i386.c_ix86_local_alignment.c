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
 scalar_t__ AGGREGATE_TYPE_P (scalar_t__) ; 
 scalar_t__ ALIGN_MODE_128 (scalar_t__) ; 
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ COMPLEX_TYPE ; 
 scalar_t__ DCmode ; 
 scalar_t__ DECL_MODE (scalar_t__) ; 
 scalar_t__ DFmode ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ QUAL_UNION_TYPE ; 
 scalar_t__ REAL_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_INT_CST_HIGH (scalar_t__) ; 
 int TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_MODE (scalar_t__) ; 
 scalar_t__ TYPE_SIZE (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 
 scalar_t__ VECTOR_TYPE ; 
 scalar_t__ XCmode ; 

int
ix86_local_alignment (tree type, int align)
{
  /* x86-64 ABI requires arrays greater than 16 bytes to be aligned
     to 16byte boundary.  */
  if (TARGET_64BIT)
    {
      if (AGGREGATE_TYPE_P (type)
	   && TYPE_SIZE (type)
	   && TREE_CODE (TYPE_SIZE (type)) == INTEGER_CST
	   && (TREE_INT_CST_LOW (TYPE_SIZE (type)) >= 128
	       || TREE_INT_CST_HIGH (TYPE_SIZE (type))) && align < 128)
	return 128;
    }
  if (TREE_CODE (type) == ARRAY_TYPE)
    {
      if (TYPE_MODE (TREE_TYPE (type)) == DFmode && align < 64)
	return 64;
      if (ALIGN_MODE_128 (TYPE_MODE (TREE_TYPE (type))) && align < 128)
	return 128;
    }
  else if (TREE_CODE (type) == COMPLEX_TYPE)
    {
      if (TYPE_MODE (type) == DCmode && align < 64)
	return 64;
      if (TYPE_MODE (type) == XCmode && align < 128)
	return 128;
    }
  else if ((TREE_CODE (type) == RECORD_TYPE
	    || TREE_CODE (type) == UNION_TYPE
	    || TREE_CODE (type) == QUAL_UNION_TYPE)
	   && TYPE_FIELDS (type))
    {
      if (DECL_MODE (TYPE_FIELDS (type)) == DFmode && align < 64)
	return 64;
      if (ALIGN_MODE_128 (DECL_MODE (TYPE_FIELDS (type))) && align < 128)
	return 128;
    }
  else if (TREE_CODE (type) == REAL_TYPE || TREE_CODE (type) == VECTOR_TYPE
	   || TREE_CODE (type) == INTEGER_TYPE)
    {

      if (TYPE_MODE (type) == DFmode && align < 64)
	return 64;
      if (ALIGN_MODE_128 (TYPE_MODE (type)) && align < 128)
	return 128;
    }
  return align;
}