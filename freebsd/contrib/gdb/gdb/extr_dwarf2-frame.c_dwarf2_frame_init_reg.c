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
struct gdbarch {int dummy; } ;
struct dwarf2_frame_state_reg {int dummy; } ;
struct dwarf2_frame_ops {int /*<<< orphan*/  (* init_reg ) (struct gdbarch*,int,struct dwarf2_frame_state_reg*) ;} ;

/* Variables and functions */
 struct dwarf2_frame_ops* dwarf2_frame_ops (struct gdbarch*) ; 
 int /*<<< orphan*/  stub1 (struct gdbarch*,int,struct dwarf2_frame_state_reg*) ; 

__attribute__((used)) static void
dwarf2_frame_init_reg (struct gdbarch *gdbarch, int regnum,
		       struct dwarf2_frame_state_reg *reg)
{
  struct dwarf2_frame_ops *ops;

  ops = dwarf2_frame_ops (gdbarch);
  ops->init_reg (gdbarch, regnum, reg);
}