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
struct agent_expr {int /*<<< orphan*/  scope; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_VIRTUAL_FRAME_POINTER (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ax_reg (struct agent_expr*,int) ; 
 int /*<<< orphan*/  gen_offset (struct agent_expr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_frame_args_address (struct agent_expr *ax)
{
  int frame_reg;
  LONGEST frame_offset;

  TARGET_VIRTUAL_FRAME_POINTER (ax->scope, &frame_reg, &frame_offset);
  ax_reg (ax, frame_reg);
  gen_offset (ax, frame_offset);
}