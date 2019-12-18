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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int MAX_MOVE_BYTES ; 
 int /*<<< orphan*/  mips_block_move_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mips_block_move_straight (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ optimize ; 

bool
mips_expand_block_move (rtx dest, rtx src, rtx length)
{
  if (GET_CODE (length) == CONST_INT)
    {
      if (INTVAL (length) <= 2 * MAX_MOVE_BYTES)
	{
	  mips_block_move_straight (dest, src, INTVAL (length));
	  return true;
	}
      else if (optimize)
	{
	  mips_block_move_loop (dest, src, INTVAL (length));
	  return true;
	}
    }
  return false;
}