#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct dwarf2_frame_state* reg; int /*<<< orphan*/  prev; } ;
struct TYPE_3__ {struct dwarf2_frame_state* reg; int /*<<< orphan*/  prev; } ;
struct dwarf2_frame_state {TYPE_2__ regs; TYPE_1__ initial; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf2_frame_state_free_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct dwarf2_frame_state*) ; 

__attribute__((used)) static void
dwarf2_frame_state_free (void *p)
{
  struct dwarf2_frame_state *fs = p;

  dwarf2_frame_state_free_regs (fs->initial.prev);
  dwarf2_frame_state_free_regs (fs->regs.prev);
  xfree (fs->initial.reg);
  xfree (fs->regs.reg);
  xfree (fs);
}