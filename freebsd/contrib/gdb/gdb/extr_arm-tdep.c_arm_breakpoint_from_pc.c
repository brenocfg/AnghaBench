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
struct gdbarch_tdep {int thumb_breakpoint_size; unsigned char const* thumb_breakpoint; int arm_breakpoint_size; unsigned char const* arm_breakpoint; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  UNMAKE_THUMB_ADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ arm_pc_is_thumb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const unsigned char *
arm_breakpoint_from_pc (CORE_ADDR *pcptr, int *lenptr)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  if (arm_pc_is_thumb (*pcptr))
    {
      *pcptr = UNMAKE_THUMB_ADDR (*pcptr);
      *lenptr = tdep->thumb_breakpoint_size;
      return tdep->thumb_breakpoint;
    }
  else
    {
      *lenptr = tdep->arm_breakpoint_size;
      return tdep->arm_breakpoint;
    }
}