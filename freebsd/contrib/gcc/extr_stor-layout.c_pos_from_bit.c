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
 int /*<<< orphan*/  bitsize_int (unsigned int) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_int (unsigned int) ; 
 int /*<<< orphan*/  sizetype ; 

void
pos_from_bit (tree *poffset, tree *pbitpos, unsigned int off_align,
	      tree pos)
{
  *poffset = size_binop (MULT_EXPR,
			 fold_convert (sizetype,
				       size_binop (FLOOR_DIV_EXPR, pos,
						   bitsize_int (off_align))),
			 size_int (off_align / BITS_PER_UNIT));
  *pbitpos = size_binop (FLOOR_MOD_EXPR, pos, bitsize_int (off_align));
}