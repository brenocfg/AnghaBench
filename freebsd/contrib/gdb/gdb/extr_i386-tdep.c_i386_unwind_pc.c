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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  PC_REGNUM ; 
 int /*<<< orphan*/  builtin_type_void_func_ptr ; 
 int /*<<< orphan*/  extract_typed_address (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_unwind_register (struct frame_info*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static CORE_ADDR
i386_unwind_pc (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  char buf[8];

  frame_unwind_register (next_frame, PC_REGNUM, buf);
  return extract_typed_address (buf, builtin_type_void_func_ptr);
}