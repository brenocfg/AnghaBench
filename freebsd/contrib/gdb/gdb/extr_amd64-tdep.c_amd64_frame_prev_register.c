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
struct frame_info {int dummy; } ;
struct amd64_frame_cache {int* saved_regs; scalar_t__ saved_sp; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int AMD64_NUM_SAVED_REGS ; 
 int SP_REGNUM ; 
 struct amd64_frame_cache* amd64_frame_cache (struct frame_info*,void**) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  frame_register_unwind (struct frame_info*,int,int*,int*,int*,int*,void*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int lval_memory ; 
 int not_lval ; 
 int /*<<< orphan*/  read_memory (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_unsigned_integer (void*,int,scalar_t__) ; 

__attribute__((used)) static void
amd64_frame_prev_register (struct frame_info *next_frame, void **this_cache,
			   int regnum, int *optimizedp,
			   enum lval_type *lvalp, CORE_ADDR *addrp,
			   int *realnump, void *valuep)
{
  struct amd64_frame_cache *cache =
    amd64_frame_cache (next_frame, this_cache);

  gdb_assert (regnum >= 0);

  if (regnum == SP_REGNUM && cache->saved_sp)
    {
      *optimizedp = 0;
      *lvalp = not_lval;
      *addrp = 0;
      *realnump = -1;
      if (valuep)
	{
	  /* Store the value.  */
	  store_unsigned_integer (valuep, 8, cache->saved_sp);
	}
      return;
    }

  if (regnum < AMD64_NUM_SAVED_REGS && cache->saved_regs[regnum] != -1)
    {
      *optimizedp = 0;
      *lvalp = lval_memory;
      *addrp = cache->saved_regs[regnum];
      *realnump = -1;
      if (valuep)
	{
	  /* Read the value in from memory.  */
	  read_memory (*addrp, valuep,
		       register_size (current_gdbarch, regnum));
	}
      return;
    }

  frame_register_unwind (next_frame, regnum,
			 optimizedp, lvalp, addrp, realnump, valuep);
}