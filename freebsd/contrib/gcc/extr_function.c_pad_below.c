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
struct args_size {int /*<<< orphan*/  constant; } ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PARM_SIZE (struct args_size,int /*<<< orphan*/ ) ; 
 int BITS_PER_UNIT ; 
 int BLKmode ; 
 int GET_MODE_BITSIZE (int) ; 
 int GET_MODE_SIZE (int) ; 
 scalar_t__ INTEGER_CST ; 
 int PARM_BOUNDARY ; 
 int /*<<< orphan*/  SUB_PARM_SIZE (struct args_size,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pad_below (struct args_size *offset_ptr, enum machine_mode passed_mode, tree sizetree)
{
  if (passed_mode != BLKmode)
    {
      if (GET_MODE_BITSIZE (passed_mode) % PARM_BOUNDARY)
	offset_ptr->constant
	  += (((GET_MODE_BITSIZE (passed_mode) + PARM_BOUNDARY - 1)
	       / PARM_BOUNDARY * PARM_BOUNDARY / BITS_PER_UNIT)
	      - GET_MODE_SIZE (passed_mode));
    }
  else
    {
      if (TREE_CODE (sizetree) != INTEGER_CST
	  || (TREE_INT_CST_LOW (sizetree) * BITS_PER_UNIT) % PARM_BOUNDARY)
	{
	  /* Round the size up to multiple of PARM_BOUNDARY bits.  */
	  tree s2 = round_up (sizetree, PARM_BOUNDARY / BITS_PER_UNIT);
	  /* Add it in.  */
	  ADD_PARM_SIZE (*offset_ptr, s2);
	  SUB_PARM_SIZE (*offset_ptr, sizetree);
	}
    }
}