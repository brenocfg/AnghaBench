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
 int /*<<< orphan*/  JUMP_LABEL (int /*<<< orphan*/ ) ; 
 scalar_t__ apply_change_group () ; 
 int /*<<< orphan*/  cancel_changes (int /*<<< orphan*/ ) ; 
 scalar_t__ invert_jump_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirect_jump_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int
invert_jump (rtx jump, rtx nlabel, int delete_unused)
{
  rtx olabel = JUMP_LABEL (jump);

  if (invert_jump_1 (jump, nlabel) && apply_change_group ())
    {
      redirect_jump_2 (jump, olabel, nlabel, delete_unused, 1);
      return 1;
    }
  cancel_changes (0);
  return 0;
}