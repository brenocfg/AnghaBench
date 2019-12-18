#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* record_layout_info ;
struct TYPE_5__ {int /*<<< orphan*/  bitpos; int /*<<< orphan*/  t; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_UNIT ; 
 scalar_t__ CLASSTYPE_AS_BASE (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INT_CST_LT_UNSIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abi_version_at_least (int) ; 
 int /*<<< orphan*/  bitsize_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitsizetype ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_of_class (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_rli (TYPE_1__*) ; 
 int /*<<< orphan*/  rli_size_unit_so_far (TYPE_1__*) ; 
 int /*<<< orphan*/  round_down (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
include_empty_classes (record_layout_info rli)
{
  tree eoc;
  tree rli_size;

  /* It might be the case that we grew the class to allocate a
     zero-sized base class.  That won't be reflected in RLI, yet,
     because we are willing to overlay multiple bases at the same
     offset.  However, now we need to make sure that RLI is big enough
     to reflect the entire class.  */
  eoc = end_of_class (rli->t,
		      CLASSTYPE_AS_BASE (rli->t) != NULL_TREE);
  rli_size = rli_size_unit_so_far (rli);
  if (TREE_CODE (rli_size) == INTEGER_CST
      && INT_CST_LT_UNSIGNED (rli_size, eoc))
    {
      if (!abi_version_at_least (2))
	/* In version 1 of the ABI, the size of a class that ends with
	   a bitfield was not rounded up to a whole multiple of a
	   byte.  Because rli_size_unit_so_far returns only the number
	   of fully allocated bytes, any extra bits were not included
	   in the size.  */
	rli->bitpos = round_down (rli->bitpos, BITS_PER_UNIT);
      else
	/* The size should have been rounded to a whole byte.  */
	gcc_assert (tree_int_cst_equal
		    (rli->bitpos, round_down (rli->bitpos, BITS_PER_UNIT)));
      rli->bitpos
	= size_binop (PLUS_EXPR,
		      rli->bitpos,
		      size_binop (MULT_EXPR,
				  convert (bitsizetype,
					   size_binop (MINUS_EXPR,
						       eoc, rli_size)),
				  bitsize_int (BITS_PER_UNIT)));
      normalize_rli (rli);
    }
}