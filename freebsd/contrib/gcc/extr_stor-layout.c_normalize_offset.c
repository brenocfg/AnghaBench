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
 unsigned int BITS_PER_UNIT ; 
 int /*<<< orphan*/  FLOOR_DIV_EXPR ; 
 int /*<<< orphan*/  FLOOR_MOD_EXPR ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  bitsize_int (unsigned int) ; 
 scalar_t__ compare_tree_int (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_int (unsigned int) ; 
 int /*<<< orphan*/  sizetype ; 

void
normalize_offset (tree *poffset, tree *pbitpos, unsigned int off_align)
{
  /* If the bit position is now larger than it should be, adjust it
     downwards.  */
  if (compare_tree_int (*pbitpos, off_align) >= 0)
    {
      tree extra_aligns = size_binop (FLOOR_DIV_EXPR, *pbitpos,
				      bitsize_int (off_align));

      *poffset
	= size_binop (PLUS_EXPR, *poffset,
		      size_binop (MULT_EXPR,
				  fold_convert (sizetype, extra_aligns),
				  size_int (off_align / BITS_PER_UNIT)));

      *pbitpos
	= size_binop (FLOOR_MOD_EXPR, *pbitpos, bitsize_int (off_align));
    }
}