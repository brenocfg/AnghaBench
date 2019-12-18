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
 scalar_t__ ALIGN_MODE_128 (scalar_t__) ; 
 int BITS_PER_WORD ; 
 scalar_t__ DFmode ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ STRING_CST ; 
 int /*<<< orphan*/  TARGET_NO_ALIGN_LONG_STRINGS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_STRING_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optimize_size ; 

int
ix86_constant_alignment (tree exp, int align)
{
  if (TREE_CODE (exp) == REAL_CST)
    {
      if (TYPE_MODE (TREE_TYPE (exp)) == DFmode && align < 64)
	return 64;
      else if (ALIGN_MODE_128 (TYPE_MODE (TREE_TYPE (exp))) && align < 128)
	return 128;
    }
  else if (!optimize_size && TREE_CODE (exp) == STRING_CST
      	   && !TARGET_NO_ALIGN_LONG_STRINGS
	   && TREE_STRING_LENGTH (exp) >= 31 && align < BITS_PER_WORD)
    return BITS_PER_WORD;

  return align;
}