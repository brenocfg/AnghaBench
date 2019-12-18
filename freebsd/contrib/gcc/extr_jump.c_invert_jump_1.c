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
 int /*<<< orphan*/  SET_SRC (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int invert_exp_1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int num_validated_changes () ; 
 scalar_t__ pc_set (scalar_t__) ; 
 scalar_t__ redirect_jump_1 (scalar_t__,scalar_t__) ; 

int
invert_jump_1 (rtx jump, rtx nlabel)
{
  rtx x = pc_set (jump);
  int ochanges;
  int ok;

  ochanges = num_validated_changes ();
  gcc_assert (x);
  ok = invert_exp_1 (SET_SRC (x), jump);
  gcc_assert (ok);
  
  if (num_validated_changes () == ochanges)
    return 0;

  /* redirect_jump_1 will fail of nlabel == olabel, and the current use is
     in Pmode, so checking this is not merely an optimization.  */
  return nlabel == JUMP_LABEL (jump) || redirect_jump_1 (jump, nlabel);
}