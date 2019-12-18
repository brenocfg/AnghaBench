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
struct i386_frame_cache {scalar_t__ locals; int sp_offset; scalar_t__* saved_regs; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 unsigned char read_memory_unsigned_integer (scalar_t__,int) ; 

__attribute__((used)) static CORE_ADDR
i386_analyze_register_saves (CORE_ADDR pc, CORE_ADDR current_pc,
			     struct i386_frame_cache *cache)
{
  CORE_ADDR offset = 0;
  unsigned char op;
  int i;

  if (cache->locals > 0)
    offset -= cache->locals;
  for (i = 0; i < 8 && pc < current_pc; i++)
    {
      op = read_memory_unsigned_integer (pc, 1);
      if (op < 0x50 || op > 0x57)
	break;

      offset -= 4;
      cache->saved_regs[op - 0x50] = offset;
      cache->sp_offset += 4;
      pc++;
    }

  return pc;
}