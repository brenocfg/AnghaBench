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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE_BITSIZE (int) ; 
 int GET_MODE_CLASS (int) ; 
 int GET_MODE_NUNITS (int) ; 
#define  MODE_INT 130 
#define  MODE_VECTOR_FLOAT 129 
#define  MODE_VECTOR_INT 128 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  make_vector_type (int /*<<< orphan*/ ,int,int) ; 

tree
build_vector_type_for_mode (tree innertype, enum machine_mode mode)
{
  int nunits;

  switch (GET_MODE_CLASS (mode))
    {
    case MODE_VECTOR_INT:
    case MODE_VECTOR_FLOAT:
      nunits = GET_MODE_NUNITS (mode);
      break;

    case MODE_INT:
      /* Check that there are no leftover bits.  */
      gcc_assert (GET_MODE_BITSIZE (mode)
		  % TREE_INT_CST_LOW (TYPE_SIZE (innertype)) == 0);

      nunits = GET_MODE_BITSIZE (mode)
	       / TREE_INT_CST_LOW (TYPE_SIZE (innertype));
      break;

    default:
      gcc_unreachable ();
    }

  return make_vector_type (innertype, nunits, mode);
}