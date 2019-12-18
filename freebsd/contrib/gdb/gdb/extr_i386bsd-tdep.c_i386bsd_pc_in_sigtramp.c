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
struct gdbarch_tdep {scalar_t__ sigtramp_start; scalar_t__ sigtramp_end; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 

int
i386bsd_pc_in_sigtramp (CORE_ADDR pc, char *name)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  return (pc >= tdep->sigtramp_start && pc < tdep->sigtramp_end);
}