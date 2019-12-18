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
struct frame_info {int dummy; } ;
struct frame_id {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_BSP_REGNUM ; 
 int /*<<< orphan*/  extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct frame_id frame_id_build_special (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 
 int /*<<< orphan*/  frame_unwind_register (struct frame_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp_regnum ; 

__attribute__((used)) static struct frame_id
ia64_unwind_dummy_id (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  char buf[8];
  CORE_ADDR sp, bsp;

  frame_unwind_register (next_frame, sp_regnum, buf);
  sp = extract_unsigned_integer (buf, 8);

  frame_unwind_register (next_frame, IA64_BSP_REGNUM, buf);
  bsp = extract_unsigned_integer (buf, 8);

  if (gdbarch_debug >= 1)
    fprintf_unfiltered (gdb_stdlog,
			"dummy frame id: code 0x%s, stack 0x%s, special 0x%s\n",
			paddr_nz (frame_pc_unwind (next_frame)), 
			paddr_nz (sp), paddr_nz (bsp));

  return frame_id_build_special (sp, frame_pc_unwind (next_frame), bsp);
}