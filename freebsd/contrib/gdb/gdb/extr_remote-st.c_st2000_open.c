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
 char* LOG_FILE ; 
 int /*<<< orphan*/  baudrate ; 
 char* dev_name ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expect_prompt (int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * log_file ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  printf_stdebug (char*) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_close (char*) ; 
 int /*<<< orphan*/  serial_open (char*) ; 
 int /*<<< orphan*/  serial_raw (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_setbaudrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  st2000_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st2000_desc ; 
 int /*<<< orphan*/  st2000_ops ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 char* target_shortname ; 

__attribute__((used)) static void
st2000_open (char *args, int from_tty)
{
  int n;
  char junk[100];

  target_preopen (from_tty);

  n = sscanf (args, " %s %d %s", dev_name, &baudrate, junk);

  if (n != 2)
    error ("Bad arguments.  Usage: target st2000 <device> <speed>\n\
or target st2000 <host> <port>\n");

  st2000_close (0);

  st2000_desc = serial_open (dev_name);

  if (!st2000_desc)
    perror_with_name (dev_name);

  if (serial_setbaudrate (st2000_desc, baudrate))
    {
      serial_close (dev_name);
      perror_with_name (dev_name);
    }

  serial_raw (st2000_desc);

  push_target (&st2000_ops);

#if defined (LOG_FILE)
  log_file = fopen (LOG_FILE, "w");
  if (log_file == NULL)
    perror_with_name (LOG_FILE);
#endif

  /* Hello?  Are you there?  */
  printf_stdebug ("\003");	/* ^C wakes up dbug */

  expect_prompt (1);

  if (from_tty)
    printf ("Remote %s connected to %s\n", target_shortname,
	    dev_name);
}