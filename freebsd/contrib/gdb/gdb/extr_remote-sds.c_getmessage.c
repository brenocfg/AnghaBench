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
 int SERIAL_TIMEOUT ; 
 int compute_checksum (int,unsigned char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fromb64 (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int message_pending ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 int read_frame (unsigned char*) ; 
 int readchar (int) ; 
 scalar_t__ remote_debug ; 
 int sds_timeout ; 
 int /*<<< orphan*/  strcpy (unsigned char*,char*) ; 
 int strlen (unsigned char*) ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 
 scalar_t__ watchdog ; 

__attribute__((used)) static int
getmessage (unsigned char *buf, int forever)
{
  int c, c2, c3;
  int tries;
  int timeout;
  int val, i, len, csum;
  unsigned char header[3];
  unsigned char inbuf[500];

  strcpy (buf, "timeout");

  if (forever)
    {
      timeout = watchdog > 0 ? watchdog : -1;
    }

  else
    timeout = sds_timeout;

#define MAX_TRIES 3

  for (tries = 1; tries <= MAX_TRIES; tries++)
    {
      /* This can loop forever if the remote side sends us characters
         continuously, but if it pauses, we'll get a zero from readchar
         because of timeout.  Then we'll count that as a retry.  */

      /* Note that we will only wait forever prior to the start of a packet.
         After that, we expect characters to arrive at a brisk pace.  They
         should show up within sds_timeout intervals.  */

      do
	{
	  c = readchar (timeout);

	  if (c == SERIAL_TIMEOUT)
	    {
	      if (forever)	/* Watchdog went off.  Kill the target. */
		{
		  target_mourn_inferior ();
		  error ("Watchdog has expired.  Target detached.\n");
		}
	      if (remote_debug)
		fputs_filtered ("Timed out.\n", gdb_stdlog);
	      goto retry;
	    }
	}
      while (c != '$' && c != '{');

      /* We might have seen a "trigraph", a sequence of three characters
         that indicate various sorts of communication state.  */

      if (c == '{')
	{
	  /* Read the other two chars of the trigraph. */
	  c2 = readchar (timeout);
	  c3 = readchar (timeout);
	  if (remote_debug)
	    fprintf_unfiltered (gdb_stdlog, "Trigraph %c%c%c received\n",
				c, c2, c3);
	  if (c3 == '+')
	    {
	      message_pending = 1;
	      return 0;		/*???? */
	    }
	  continue;
	}

      val = read_frame (inbuf);

      if (val == 1)
	{
	  fromb64 (inbuf, header, 4);
	  /* (should check out other bits) */
	  fromb64 (inbuf + 4, buf, strlen (inbuf) - 4);

	  len = header[2];

	  csum = 0;
	  csum = compute_checksum (csum, buf, len);
	  csum = compute_checksum (csum, header + 1, 2);

	  if (csum != header[0])
	    fprintf_unfiltered (gdb_stderr,
			    "Checksum mismatch: computed %d, received %d\n",
				csum, header[0]);

	  if (header[2] == 0xff)
	    fprintf_unfiltered (gdb_stderr, "Requesting resend...\n");

	  if (remote_debug)
	    {
	      fprintf_unfiltered (gdb_stdlog,
				"... (Got checksum %d, id %d, length %d)\n",
				  header[0], header[1], header[2]);
	      fprintf_unfiltered (gdb_stdlog, "Message received: \"");
	      for (i = 0; i < len; ++i)
		{
		  fprintf_unfiltered (gdb_stdlog, "%02x", (unsigned char) buf[i]);
		}
	      fprintf_unfiltered (gdb_stdlog, "\"\n");
	    }

	  /* no ack required? */
	  return len;
	}

      /* Try the whole thing again.  */
    retry:
      /* need to do something here */
      ;
    }

  /* We have tried hard enough, and just can't receive the packet.  Give up. */

  printf_unfiltered ("Ignoring packet error, continuing...\n");
  return 0;
}