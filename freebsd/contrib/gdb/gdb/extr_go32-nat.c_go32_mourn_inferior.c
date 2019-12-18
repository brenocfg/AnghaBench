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

/* Variables and functions */
 int /*<<< orphan*/  generic_mourn_inferior () ; 
 int /*<<< orphan*/  go32_kill_inferior () ; 
 int /*<<< orphan*/  i386_cleanup_dregs () ; 

__attribute__((used)) static void
go32_mourn_inferior (void)
{
  /* We need to make sure all the breakpoint enable bits in the DR7
     register are reset when the inferior exits.  Otherwise, if they
     rerun the inferior, the uncleared bits may cause random SIGTRAPs,
     failure to set more watchpoints, and other calamities.  It would
     be nice if GDB itself would take care to remove all breakpoints
     at all times, but it doesn't, probably under an assumption that
     the OS cleans up when the debuggee exits.  */
  i386_cleanup_dregs ();
  go32_kill_inferior ();
  generic_mourn_inferior ();
}