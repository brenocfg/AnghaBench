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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  I386_EBP_REGNUM ; 
 scalar_t__ extract_unsigned_integer (char*,int) ; 
 struct frame_id frame_id_build (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 
 int /*<<< orphan*/  frame_unwind_register (struct frame_info*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct frame_id
i386_unwind_dummy_id (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  char buf[4];
  CORE_ADDR fp;

  frame_unwind_register (next_frame, I386_EBP_REGNUM, buf);
  fp = extract_unsigned_integer (buf, 4);

  /* See the end of i386_push_dummy_call.  */
  return frame_id_build (fp + 8, frame_pc_unwind (next_frame));
}