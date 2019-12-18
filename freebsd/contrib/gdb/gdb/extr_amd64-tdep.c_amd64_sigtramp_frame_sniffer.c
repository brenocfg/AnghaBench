#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct frame_unwind {int dummy; } ;
struct frame_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sigcontext_addr; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ PC_IN_SIGTRAMP (int /*<<< orphan*/ ,char*) ; 
 struct frame_unwind const amd64_sigtramp_frame_unwind ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  find_pc_partial_function (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* gdbarch_tdep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct frame_unwind *
amd64_sigtramp_frame_sniffer (struct frame_info *next_frame)
{
  CORE_ADDR pc = frame_pc_unwind (next_frame);
  char *name;

  find_pc_partial_function (pc, &name, NULL, NULL);
  if (PC_IN_SIGTRAMP (pc, name))
    {
      gdb_assert (gdbarch_tdep (current_gdbarch)->sigcontext_addr);

      return &amd64_sigtramp_frame_unwind;
    }

  return NULL;
}