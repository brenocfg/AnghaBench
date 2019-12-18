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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ JUMP_LABEL (scalar_t__) ; 
 int /*<<< orphan*/  apply_change_group () ; 
 int /*<<< orphan*/  redirect_jump_1 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  redirect_jump_2 (scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 

int
redirect_jump (rtx jump, rtx nlabel, int delete_unused)
{
  rtx olabel = JUMP_LABEL (jump);

  if (nlabel == olabel)
    return 1;

  if (! redirect_jump_1 (jump, nlabel) || ! apply_change_group ())
    return 0;

  redirect_jump_2 (jump, olabel, nlabel, delete_unused, 0);
  return 1;
}