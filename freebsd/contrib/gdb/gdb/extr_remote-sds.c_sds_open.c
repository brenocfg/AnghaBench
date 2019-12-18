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
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int baud_rate ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int just_started ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  pop_target () ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 
 int /*<<< orphan*/  sds_desc ; 
 int /*<<< orphan*/  sds_ops ; 
 int /*<<< orphan*/  sds_start_remote ; 
 int /*<<< orphan*/  serial_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_flush_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_open (char*) ; 
 int /*<<< orphan*/  serial_raw (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_setbaudrate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sds_open (char *name, int from_tty)
{
  if (name == 0)
    error ("To open a remote debug connection, you need to specify what serial\n\
device is attached to the remote system (e.g. /dev/ttya).");

  target_preopen (from_tty);

  unpush_target (&sds_ops);

  sds_desc = serial_open (name);
  if (!sds_desc)
    perror_with_name (name);

  if (baud_rate != -1)
    {
      if (serial_setbaudrate (sds_desc, baud_rate))
	{
	  serial_close (sds_desc);
	  perror_with_name (name);
	}
    }


  serial_raw (sds_desc);

  /* If there is something sitting in the buffer we might take it as a
     response to a command, which would be bad.  */
  serial_flush_input (sds_desc);

  if (from_tty)
    {
      puts_filtered ("Remote debugging using ");
      puts_filtered (name);
      puts_filtered ("\n");
    }
  push_target (&sds_ops);	/* Switch to using remote target now */

  just_started = 1;

  /* Start the remote connection; if error (0), discard this target.
     In particular, if the user quits, be sure to discard it (we'd be
     in an inconsistent state otherwise).  */
  if (!catch_errors (sds_start_remote, NULL,
		     "Couldn't establish connection to remote target\n",
		     RETURN_MASK_ALL))
    pop_target ();
}