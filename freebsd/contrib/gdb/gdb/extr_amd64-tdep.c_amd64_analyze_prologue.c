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
struct amd64_frame_cache {int sp_offset; scalar_t__ frameless_p; scalar_t__* saved_regs; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 size_t AMD64_RBP_REGNUM ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  read_memory (scalar_t__,unsigned char*,int) ; 
 unsigned char read_memory_unsigned_integer (scalar_t__,int) ; 

__attribute__((used)) static CORE_ADDR
amd64_analyze_prologue (CORE_ADDR pc, CORE_ADDR current_pc,
			struct amd64_frame_cache *cache)
{
  static unsigned char proto[3] = { 0x48, 0x89, 0xe5 };
  unsigned char buf[3];
  unsigned char op;

  if (current_pc <= pc)
    return current_pc;

  op = read_memory_unsigned_integer (pc, 1);

  if (op == 0x55)		/* pushq %rbp */
    {
      /* Take into account that we've executed the `pushq %rbp' that
         starts this instruction sequence.  */
      cache->saved_regs[AMD64_RBP_REGNUM] = 0;
      cache->sp_offset += 8;

      /* If that's all, return now.  */
      if (current_pc <= pc + 1)
        return current_pc;

      /* Check for `movq %rsp, %rbp'.  */
      read_memory (pc + 1, buf, 3);
      if (memcmp (buf, proto, 3) != 0)
	return pc + 1;

      /* OK, we actually have a frame.  */
      cache->frameless_p = 0;
      return pc + 4;
    }

  return pc;
}