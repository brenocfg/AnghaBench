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
struct frame_id {int dummy; } ;
struct dummy_frame {int /*<<< orphan*/  regcache; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  dummy_frame_this_id (struct frame_info*,void**,struct frame_id*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int not_lval ; 
 int /*<<< orphan*/  regcache_cooked_read (int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static void
dummy_frame_prev_register (struct frame_info *next_frame,
			   void **this_prologue_cache,
			   int regnum, int *optimized,
			   enum lval_type *lvalp, CORE_ADDR *addrp,
			   int *realnum, void *bufferp)
{
  struct dummy_frame *dummy;
  struct frame_id id;

  /* Call the ID method which, if at all possible, will set the
     prologue cache.  */
  dummy_frame_this_id (next_frame, this_prologue_cache, &id);
  dummy = (*this_prologue_cache);
  gdb_assert (dummy != NULL);

  /* Describe the register's location.  Generic dummy frames always
     have the register value in an ``expression''.  */
  *optimized = 0;
  *lvalp = not_lval;
  *addrp = 0;
  *realnum = -1;

  /* If needed, find and return the value of the register.  */
  if (bufferp != NULL)
    {
      /* Return the actual value.  */
      /* Use the regcache_cooked_read() method so that it, on the fly,
         constructs either a raw or pseudo register from the raw
         register cache.  */
      regcache_cooked_read (dummy->regcache, regnum, bufferp);
    }
}