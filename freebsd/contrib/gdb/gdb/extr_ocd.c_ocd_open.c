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
struct target_ops {int dummy; } ;
typedef  enum ocd_target_type { ____Placeholder_ocd_target_type } ocd_target_type ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int baud_rate ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,int*,char*,int /*<<< orphan*/ ) ; 
 struct target_ops* current_ops ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  ocd_desc ; 
 int /*<<< orphan*/  ocd_start_remote ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  pop_target () ; 
 int /*<<< orphan*/  push_target (struct target_ops*) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 
 int /*<<< orphan*/  serial_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_flush_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_open (char*) ; 
 int /*<<< orphan*/  serial_raw (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_setbaudrate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 int /*<<< orphan*/  unpush_target (struct target_ops*) ; 

void
ocd_open (char *name, int from_tty, enum ocd_target_type target_type,
	  struct target_ops *ops)
{
  unsigned char buf[10], *p;
  int pktlen;

  if (name == 0)
    error ("To open an OCD connection, you need to specify the\n\
device the OCD device is attached to (e.g. /dev/ttya).");

  target_preopen (from_tty);

  current_ops = ops;

  unpush_target (current_ops);

  ocd_desc = serial_open (name);
  if (!ocd_desc)
    perror_with_name (name);

  if (baud_rate != -1)
    {
      if (serial_setbaudrate (ocd_desc, baud_rate))
	{
	  serial_close (ocd_desc);
	  perror_with_name (name);
	}
    }

  serial_raw (ocd_desc);

  /* If there is something sitting in the buffer we might take it as a
     response to a command, which would be bad.  */
  serial_flush_input (ocd_desc);

  if (from_tty)
    {
      puts_filtered ("Remote target wiggler connected to ");
      puts_filtered (name);
      puts_filtered ("\n");
    }
  push_target (current_ops);	/* Switch to using remote target now */

  /* Without this, some commands which require an active target (such as kill)
     won't work.  This variable serves (at least) double duty as both the pid
     of the target process (if it has such), and as a flag indicating that a
     target is active.  These functions should be split out into seperate
     variables, especially since GDB will someday have a notion of debugging
     several processes.  */

  inferior_ptid = pid_to_ptid (42000);
  /* Start the remote connection; if error (0), discard this target.
     In particular, if the user quits, be sure to discard it
     (we'd be in an inconsistent state otherwise).  */
  if (!catch_errors (ocd_start_remote, &target_type,
		     "Couldn't establish connection to remote target\n",
		     RETURN_MASK_ALL))
    {
      pop_target ();
      error ("Failed to connect to OCD.");
    }
}