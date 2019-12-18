#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {size_t index; } ;

/* Variables and functions */
 scalar_t__ CALL_P (scalar_t__) ; 
 int INSN_CUID (scalar_t__) ; 
 scalar_t__ MEM_READONLY_P (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ gcse_mem_operand ; 
 scalar_t__ gcse_mems_conflict_p ; 
 int /*<<< orphan*/  mems_conflict_for_gcse_p ; 
 scalar_t__* modify_mem_list ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
load_killed_in_block_p (basic_block bb, int uid_limit, rtx x, int avail_p)
{
  rtx list_entry = modify_mem_list[bb->index];

  /* If this is a readonly then we aren't going to be changing it.  */
  if (MEM_READONLY_P (x))
    return 0;

  while (list_entry)
    {
      rtx setter;
      /* Ignore entries in the list that do not apply.  */
      if ((avail_p
	   && INSN_CUID (XEXP (list_entry, 0)) < uid_limit)
	  || (! avail_p
	      && INSN_CUID (XEXP (list_entry, 0)) > uid_limit))
	{
	  list_entry = XEXP (list_entry, 1);
	  continue;
	}

      setter = XEXP (list_entry, 0);

      /* If SETTER is a call everything is clobbered.  Note that calls
	 to pure functions are never put on the list, so we need not
	 worry about them.  */
      if (CALL_P (setter))
	return 1;

      /* SETTER must be an INSN of some kind that sets memory.  Call
	 note_stores to examine each hunk of memory that is modified.

	 The note_stores interface is pretty limited, so we have to
	 communicate via global variables.  Yuk.  */
      gcse_mem_operand = x;
      gcse_mems_conflict_p = 0;
      note_stores (PATTERN (setter), mems_conflict_for_gcse_p, NULL);
      if (gcse_mems_conflict_p)
	return 1;
      list_entry = XEXP (list_entry, 1);
    }
  return 0;
}