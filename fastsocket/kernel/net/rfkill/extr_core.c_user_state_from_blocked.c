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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 unsigned long RFKILL_BLOCK_HW ; 
 unsigned long RFKILL_BLOCK_SW ; 
 int /*<<< orphan*/  RFKILL_USER_STATE_HARD_BLOCKED ; 
 int /*<<< orphan*/  RFKILL_USER_STATE_SOFT_BLOCKED ; 
 int /*<<< orphan*/  RFKILL_USER_STATE_UNBLOCKED ; 

__attribute__((used)) static u8 user_state_from_blocked(unsigned long state)
{
	if (state & RFKILL_BLOCK_HW)
		return RFKILL_USER_STATE_HARD_BLOCKED;
	if (state & RFKILL_BLOCK_SW)
		return RFKILL_USER_STATE_SOFT_BLOCKED;

	return RFKILL_USER_STATE_UNBLOCKED;
}