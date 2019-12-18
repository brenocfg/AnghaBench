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
struct frame_info {scalar_t__ pc; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  SP_REGNUM ; 
 scalar_t__ memcmp (char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  read_memory_nobpt (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  read_memory_unsigned_integer (scalar_t__,int) ; 
 scalar_t__ read_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
i386lynx_saved_pc_after_call (struct frame_info *frame)
{
  char opcode[7];
  static const unsigned char call_inst[] =
  { 0x9a, 0, 0, 0, 0, 8, 0 };	/* lcall 0x8,0x0 */

  read_memory_nobpt (frame->pc - 7, opcode, 7);
  if (memcmp (opcode, call_inst, 7) == 0)
    return read_memory_unsigned_integer (read_register (SP_REGNUM) + 4, 4);

  return read_memory_unsigned_integer (read_register (SP_REGNUM), 4);
}