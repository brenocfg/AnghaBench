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
 scalar_t__ CONSTANT_ADDRESS_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_force_addr ; 
 scalar_t__ memory_address_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_equiv_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_anchored_address (int /*<<< orphan*/ ) ; 

rtx
validize_mem (rtx ref)
{
  if (!MEM_P (ref))
    return ref;
  ref = use_anchored_address (ref);
  if (! (flag_force_addr && CONSTANT_ADDRESS_P (XEXP (ref, 0)))
      && memory_address_p (GET_MODE (ref), XEXP (ref, 0)))
    return ref;

  /* Don't alter REF itself, since that is probably a stack slot.  */
  return replace_equiv_address (ref, XEXP (ref, 0));
}