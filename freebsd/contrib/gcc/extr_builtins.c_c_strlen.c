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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ COMPOUND_EXPR ; 
 scalar_t__ COND_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (scalar_t__) ; 
 int TREE_STRING_LENGTH (scalar_t__) ; 
 char* TREE_STRING_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  host_integerp (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ size_diffop (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  size_int (int) ; 
 scalar_t__ ssize_int (int /*<<< orphan*/ ) ; 
 scalar_t__ string_constant (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ tree_int_cst_equal (scalar_t__,scalar_t__) ; 
 int tree_low_cst (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

tree
c_strlen (tree src, int only_value)
{
  tree offset_node;
  HOST_WIDE_INT offset;
  int max;
  const char *ptr;

  STRIP_NOPS (src);
  if (TREE_CODE (src) == COND_EXPR
      && (only_value || !TREE_SIDE_EFFECTS (TREE_OPERAND (src, 0))))
    {
      tree len1, len2;

      len1 = c_strlen (TREE_OPERAND (src, 1), only_value);
      len2 = c_strlen (TREE_OPERAND (src, 2), only_value);
      if (tree_int_cst_equal (len1, len2))
	return len1;
    }

  if (TREE_CODE (src) == COMPOUND_EXPR
      && (only_value || !TREE_SIDE_EFFECTS (TREE_OPERAND (src, 0))))
    return c_strlen (TREE_OPERAND (src, 1), only_value);

  src = string_constant (src, &offset_node);
  if (src == 0)
    return 0;

  max = TREE_STRING_LENGTH (src) - 1;
  ptr = TREE_STRING_POINTER (src);

  if (offset_node && TREE_CODE (offset_node) != INTEGER_CST)
    {
      /* If the string has an internal zero byte (e.g., "foo\0bar"), we can't
	 compute the offset to the following null if we don't know where to
	 start searching for it.  */
      int i;

      for (i = 0; i < max; i++)
	if (ptr[i] == 0)
	  return 0;

      /* We don't know the starting offset, but we do know that the string
	 has no internal zero bytes.  We can assume that the offset falls
	 within the bounds of the string; otherwise, the programmer deserves
	 what he gets.  Subtract the offset from the length of the string,
	 and return that.  This would perhaps not be valid if we were dealing
	 with named arrays in addition to literal string constants.  */

      return size_diffop (size_int (max), offset_node);
    }

  /* We have a known offset into the string.  Start searching there for
     a null character if we can represent it as a single HOST_WIDE_INT.  */
  if (offset_node == 0)
    offset = 0;
  else if (! host_integerp (offset_node, 0))
    offset = -1;
  else
    offset = tree_low_cst (offset_node, 0);

  /* If the offset is known to be out of bounds, warn, and call strlen at
     runtime.  */
  if (offset < 0 || offset > max)
    {
      warning (0, "offset outside bounds of constant string");
      return 0;
    }

  /* Use strlen to search for the first zero byte.  Since any strings
     constructed with build_string will have nulls appended, we win even
     if we get handed something like (char[4])"abcd".

     Since OFFSET is our starting index into the string, no further
     calculation is needed.  */
  return ssize_int (strlen (ptr + offset));
}