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
 int FALSE ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  may_trap_p (int /*<<< orphan*/ ) ; 
 scalar_t__ side_effects_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
noce_operand_ok (rtx op)
{
  /* We special-case memories, so handle any of them with
     no address side effects.  */
  if (MEM_P (op))
    return ! side_effects_p (XEXP (op, 0));

  if (side_effects_p (op))
    return FALSE;

  return ! may_trap_p (op);
}