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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  xkb_state ; 
 int /*<<< orphan*/  xkb_state_update_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void handle_xkb_state_mask(uint32_t depressed,
      uint32_t latched, uint32_t locked, uint32_t group)
{
   if (!xkb_state)
      return;
   xkb_state_update_mask(xkb_state, depressed, latched, locked, 0, 0, group);
}