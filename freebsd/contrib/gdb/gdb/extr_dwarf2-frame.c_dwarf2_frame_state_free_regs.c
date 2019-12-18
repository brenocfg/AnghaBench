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
struct dwarf2_frame_state_reg_info {struct dwarf2_frame_state_reg_info* reg; struct dwarf2_frame_state_reg_info* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct dwarf2_frame_state_reg_info*) ; 

__attribute__((used)) static void
dwarf2_frame_state_free_regs (struct dwarf2_frame_state_reg_info *rs)
{
  if (rs)
    {
      dwarf2_frame_state_free_regs (rs->prev);

      xfree (rs->reg);
      xfree (rs);
    }
}