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
struct dwarf2_frame_state_reg_info {int num_regs; struct dwarf2_frame_state_reg* reg; } ;
struct dwarf2_frame_state_reg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct dwarf2_frame_state_reg*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xrealloc (struct dwarf2_frame_state_reg*,int) ; 

__attribute__((used)) static void
dwarf2_frame_state_alloc_regs (struct dwarf2_frame_state_reg_info *rs,
			       int num_regs)
{
  size_t size = sizeof (struct dwarf2_frame_state_reg);

  if (num_regs <= rs->num_regs)
    return;

  rs->reg = (struct dwarf2_frame_state_reg *)
    xrealloc (rs->reg, num_regs * size);

  /* Initialize newly allocated registers.  */
  memset (rs->reg + rs->num_regs, 0, (num_regs - rs->num_regs) * size);
  rs->num_regs = num_regs;
}