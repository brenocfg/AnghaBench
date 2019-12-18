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
 int DWARF2_REG_TO_REGNUM (int) ; 
 scalar_t__ alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  extract_typed_address (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_unwind_register (struct frame_info*,int,char*) ; 
 struct gdbarch* get_frame_arch (struct frame_info*) ; 
 int /*<<< orphan*/  register_size (struct gdbarch*,int) ; 

__attribute__((used)) static CORE_ADDR
read_reg (void *baton, int reg)
{
  struct frame_info *next_frame = (struct frame_info *) baton;
  struct gdbarch *gdbarch = get_frame_arch (next_frame);
  int regnum;
  char *buf;

  regnum = DWARF2_REG_TO_REGNUM (reg);

  buf = (char *) alloca (register_size (gdbarch, regnum));
  frame_unwind_register (next_frame, regnum, buf);
  return extract_typed_address (buf, builtin_type_void_data_ptr);
}