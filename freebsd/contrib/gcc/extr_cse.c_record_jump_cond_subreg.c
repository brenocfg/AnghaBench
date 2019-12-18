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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  lowpart_subreg (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
record_jump_cond_subreg (enum machine_mode mode, rtx op)
{
  enum machine_mode op_mode = GET_MODE (op);
  if (op_mode == mode || op_mode == VOIDmode)
    return op;
  return lowpart_subreg (mode, op, op_mode);
}