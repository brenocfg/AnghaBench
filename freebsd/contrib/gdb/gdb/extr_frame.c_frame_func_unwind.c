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
struct TYPE_2__ {int p; int /*<<< orphan*/  addr; } ;
struct frame_info {TYPE_1__ prev_func; int /*<<< orphan*/  level; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_debug ; 
 int /*<<< orphan*/  frame_unwind_address_in_block (struct frame_info*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  get_pc_function_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 

CORE_ADDR
frame_func_unwind (struct frame_info *fi)
{
  if (!fi->prev_func.p)
    {
      /* Make certain that this, and not the adjacent, function is
         found.  */
      CORE_ADDR addr_in_block = frame_unwind_address_in_block (fi);
      fi->prev_func.p = 1;
      fi->prev_func.addr = get_pc_function_start (addr_in_block);
      if (frame_debug)
	fprintf_unfiltered (gdb_stdlog,
			    "{ frame_func_unwind (fi=%d) -> 0x%s }\n",
			    fi->level, paddr_nz (fi->prev_func.addr));
    }
  return fi->prev_func.addr;
}