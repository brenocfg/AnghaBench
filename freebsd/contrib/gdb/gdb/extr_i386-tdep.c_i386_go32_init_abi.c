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
struct gdbarch_tdep {int jb_pc_offset; } ;
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 
 int /*<<< orphan*/  i386_go32_pc_in_sigtramp ; 
 int /*<<< orphan*/  set_gdbarch_pc_in_sigtramp (struct gdbarch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
i386_go32_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  set_gdbarch_pc_in_sigtramp (gdbarch, i386_go32_pc_in_sigtramp);

  tdep->jb_pc_offset = 36;
}