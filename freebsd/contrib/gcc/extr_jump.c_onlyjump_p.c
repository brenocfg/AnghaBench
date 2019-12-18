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
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JUMP_P (int /*<<< orphan*/ *) ; 
 scalar_t__ PC ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ *) ; 
 scalar_t__ side_effects_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * single_set (int /*<<< orphan*/ *) ; 

int
onlyjump_p (rtx insn)
{
  rtx set;

  if (!JUMP_P (insn))
    return 0;

  set = single_set (insn);
  if (set == NULL)
    return 0;
  if (GET_CODE (SET_DEST (set)) != PC)
    return 0;
  if (side_effects_p (SET_SRC (set)))
    return 0;

  return 1;
}