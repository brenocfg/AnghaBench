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
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_2__ {int flags; scalar_t__ loadresp; int /*<<< orphan*/  load; int /*<<< orphan*/  (* load_routine ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MO_SREC_ACK ; 
 int /*<<< orphan*/  SREC_ALL ; 
 int /*<<< orphan*/  bfd_get_start_address (scalar_t__) ; 
 TYPE_1__* current_monitor ; 
 scalar_t__ exec_bfd ; 
 int /*<<< orphan*/  hashmark ; 
 int /*<<< orphan*/  load_srec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  monitor_debug (char*) ; 
 int /*<<< orphan*/  monitor_desc ; 
 int /*<<< orphan*/  monitor_expect (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_printf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * monitor_wait_srec_ack ; 
 int sscanf (char*,char*,char*,unsigned long*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
monitor_load (char *file, int from_tty)
{
  monitor_debug ("MON load\n");

  if (current_monitor->load_routine)
    current_monitor->load_routine (monitor_desc, file, hashmark);
  else
    {				/* The default is ascii S-records */
      int n;
      unsigned long load_offset;
      char buf[128];

      /* enable user to specify address for downloading as 2nd arg to load */
      n = sscanf (file, "%s 0x%lx", buf, &load_offset);
      if (n > 1)
	file = buf;
      else
	load_offset = 0;

      monitor_printf (current_monitor->load);
      if (current_monitor->loadresp)
	monitor_expect (current_monitor->loadresp, NULL, 0);

      load_srec (monitor_desc, file, (bfd_vma) load_offset,
		 32, SREC_ALL, hashmark,
		 current_monitor->flags & MO_SREC_ACK ?
		 monitor_wait_srec_ack : NULL);

      monitor_expect_prompt (NULL, 0);
    }

  /* Finally, make the PC point at the start address */
  if (exec_bfd)
    write_pc (bfd_get_start_address (exec_bfd));

  /* There used to be code here which would clear inferior_ptid and
     call clear_symtab_users.  None of that should be necessary:
     monitor targets should behave like remote protocol targets, and
     since generic_load does none of those things, this function
     shouldn't either.

     Furthermore, clearing inferior_ptid is *incorrect*.  After doing
     a load, we still have a valid connection to the monitor, with a
     live processor state to fiddle with.  The user can type
     `continue' or `jump *start' and make the program run.  If they do
     these things, however, GDB will be talking to a running program
     while inferior_ptid is null_ptid; this makes things like
     reinit_frame_cache very confused.  */
}