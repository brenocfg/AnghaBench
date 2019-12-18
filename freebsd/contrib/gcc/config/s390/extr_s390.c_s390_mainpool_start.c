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
struct constant_pool {int size; scalar_t__ pool_insn; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CALL_INSN ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ INSN ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ SET ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 int /*<<< orphan*/  TARGET_CPU_ZARCH ; 
 scalar_t__ UNSPECV_MAIN_POOL ; 
 scalar_t__ UNSPEC_VOLATILE ; 
 scalar_t__ XINT (scalar_t__,int) ; 
 int /*<<< orphan*/  find_constant_pool_ref (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_insns () ; 
 scalar_t__ get_pool_constant (scalar_t__) ; 
 int get_pool_mode (scalar_t__) ; 
 int /*<<< orphan*/  remove_insn (scalar_t__) ; 
 int /*<<< orphan*/  s390_add_constant (struct constant_pool*,scalar_t__,int) ; 
 int /*<<< orphan*/  s390_add_execute (struct constant_pool*,scalar_t__) ; 
 struct constant_pool* s390_alloc_pool () ; 
 scalar_t__ s390_execute_label (scalar_t__) ; 
 int /*<<< orphan*/  s390_free_pool (struct constant_pool*) ; 

__attribute__((used)) static struct constant_pool *
s390_mainpool_start (void)
{
  struct constant_pool *pool;
  rtx insn;

  pool = s390_alloc_pool ();

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    {
      if (GET_CODE (insn) == INSN
	  && GET_CODE (PATTERN (insn)) == SET
	  && GET_CODE (SET_SRC (PATTERN (insn))) == UNSPEC_VOLATILE
	  && XINT (SET_SRC (PATTERN (insn)), 1) == UNSPECV_MAIN_POOL)
	{
	  gcc_assert (!pool->pool_insn);
	  pool->pool_insn = insn;
	}

      if (!TARGET_CPU_ZARCH && s390_execute_label (insn))
	{
	  s390_add_execute (pool, insn);
	}
      else if (GET_CODE (insn) == INSN || GET_CODE (insn) == CALL_INSN)
	{
	  rtx pool_ref = NULL_RTX;
	  find_constant_pool_ref (PATTERN (insn), &pool_ref);
	  if (pool_ref)
	    {
	      rtx constant = get_pool_constant (pool_ref);
	      enum machine_mode mode = get_pool_mode (pool_ref);
	      s390_add_constant (pool, constant, mode);
	    }
	}
    }

  gcc_assert (pool->pool_insn || pool->size == 0);

  if (pool->size >= 4096)
    {
      /* We're going to chunkify the pool, so remove the main
	 pool placeholder insn.  */
      remove_insn (pool->pool_insn);

      s390_free_pool (pool);
      pool = NULL;
    }

  return pool;
}