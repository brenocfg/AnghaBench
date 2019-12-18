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
 int MAX_TRIES ; 
 int /*<<< orphan*/  QUIT ; 
 int SERIAL_TIMEOUT ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputstr_unfiltered (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 int read_frame (char*,long) ; 
 int readchar (int) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  remote_desc ; 
 int remote_timeout ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 
 scalar_t__ watchdog ; 

__attribute__((used)) static int
getpkt_sane (char *buf,
	long sizeof_buf,
	int forever)
{
  int c;
  int tries;
  int timeout;
  int val;

  strcpy (buf, "timeout");

  if (forever)
    {
      timeout = watchdog > 0 ? watchdog : -1;
    }

  else
    timeout = remote_timeout;

#define MAX_TRIES 3

  for (tries = 1; tries <= MAX_TRIES; tries++)
    {
      /* This can loop forever if the remote side sends us characters
         continuously, but if it pauses, we'll get a zero from readchar
         because of timeout.  Then we'll count that as a retry.  */

      /* Note that we will only wait forever prior to the start of a packet.
         After that, we expect characters to arrive at a brisk pace.  They
         should show up within remote_timeout intervals.  */

      do
	{
	  c = readchar (timeout);

	  if (c == SERIAL_TIMEOUT)
	    {
	      if (forever)	/* Watchdog went off?  Kill the target. */
		{
		  QUIT;
		  target_mourn_inferior ();
		  error ("Watchdog has expired.  Target detached.\n");
		}
	      if (remote_debug)
		fputs_filtered ("Timed out.\n", gdb_stdlog);
	      goto retry;
	    }
	}
      while (c != '$');

      /* We've found the start of a packet, now collect the data.  */

      val = read_frame (buf, sizeof_buf);

      if (val >= 0)
	{
	  if (remote_debug)
	    {
	      fprintf_unfiltered (gdb_stdlog, "Packet received: ");
	      fputstr_unfiltered (buf, 0, gdb_stdlog);
	      fprintf_unfiltered (gdb_stdlog, "\n");
	    }
	  serial_write (remote_desc, "+", 1);
	  return 0;
	}

      /* Try the whole thing again.  */
    retry:
      serial_write (remote_desc, "-", 1);
    }

  /* We have tried hard enough, and just can't receive the packet.  Give up. */

  printf_unfiltered ("Ignoring packet error, continuing...\n");
  serial_write (remote_desc, "+", 1);
  return 1;
}