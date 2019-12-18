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
struct temp_slot {int addr_taken; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (scalar_t__) ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 struct temp_slot* find_temp_slot_from_address (int /*<<< orphan*/ ) ; 

void
mark_temp_addr_taken (rtx x)
{
  struct temp_slot *p;

  if (x == 0)
    return;

  /* If X is not in memory or is at a constant address, it cannot be in
     a temporary slot.  */
  if (!MEM_P (x) || CONSTANT_P (XEXP (x, 0)))
    return;

  p = find_temp_slot_from_address (XEXP (x, 0));
  if (p != 0)
    p->addr_taken = 1;
}