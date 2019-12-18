#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symtabs_and_lines {int nelts; TYPE_1__* sals; } ;
struct TYPE_2__ {int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 scalar_t__ PC_REQUIRES_RUN_BEFORE_USE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  resolve_sal_pc (TYPE_1__*) ; 

__attribute__((used)) static void
breakpoint_sals_to_pc (struct symtabs_and_lines *sals,
		       char *address)
{    
  int i;
  for (i = 0; i < sals->nelts; i++)
    {
      resolve_sal_pc (&sals->sals[i]);

      /* It's possible for the PC to be nonzero, but still an illegal
         value on some targets.

         For example, on HP-UX if you start gdb, and before running the
         inferior you try to set a breakpoint on a shared library function
         "foo" where the inferior doesn't call "foo" directly but does
         pass its address to another function call, then we do find a
         minimal symbol for the "foo", but it's address is invalid.
         (Appears to be an index into a table that the loader sets up
         when the inferior is run.)

         Give the target a chance to bless sals.sals[i].pc before we
         try to make a breakpoint for it. */
      if (PC_REQUIRES_RUN_BEFORE_USE (sals->sals[i].pc))
	{
	  if (address == NULL)
	    error ("Cannot break without a running program.");
	  else
	    error ("Cannot break on %s without a running program.", 
		   address);
	}
    }
}