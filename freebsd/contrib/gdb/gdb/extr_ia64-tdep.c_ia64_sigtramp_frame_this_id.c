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
struct ia64_frame_cache {int /*<<< orphan*/  bsp; int /*<<< orphan*/  base; } ;
struct frame_info {int dummy; } ;
struct frame_id {int /*<<< orphan*/  stack_addr; int /*<<< orphan*/  code_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct frame_info*) ; 
 struct frame_id frame_id_build_special (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 struct ia64_frame_cache* ia64_sigtramp_frame_cache (struct frame_info*,void**) ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ia64_sigtramp_frame_this_id (struct frame_info *next_frame,
			       void **this_cache, struct frame_id *this_id)
{
  struct ia64_frame_cache *cache =
    ia64_sigtramp_frame_cache (next_frame, this_cache);

  (*this_id) = frame_id_build_special (cache->base, frame_pc_unwind (next_frame), cache->bsp);
  if (gdbarch_debug >= 1)
    fprintf_unfiltered (gdb_stdlog,
			"sigtramp frame id: code 0x%s, stack 0x%s, special 0x%s, next_frame %p\n",
			paddr_nz (this_id->code_addr), 
			paddr_nz (this_id->stack_addr), 
			paddr_nz (cache->bsp), next_frame);
}