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
 int /*<<< orphan*/  baudrate ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name ; 
 int /*<<< orphan*/  e7000_desc ; 
 int /*<<< orphan*/  e7000_ops ; 
 int e7000_parse_device (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e7000_start_remote ; 
 int /*<<< orphan*/  perror_with_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_raw (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_setbaudrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 int /*<<< orphan*/  target_shortname ; 

__attribute__((used)) static void
e7000_open (char *args, int from_tty)
{
  int n;

  target_preopen (from_tty);

  n = e7000_parse_device (args, dev_name, baudrate);

  push_target (&e7000_ops);

  e7000_desc = serial_open (dev_name);

  if (!e7000_desc)
    perror_with_name (dev_name);

  if (serial_setbaudrate (e7000_desc, baudrate))
    {
      serial_close (e7000_desc);
      perror_with_name (dev_name);
    }
  serial_raw (e7000_desc);

  /* Start the remote connection; if error (0), discard this target.
     In particular, if the user quits, be sure to discard it
     (we'd be in an inconsistent state otherwise).  */
  if (!catch_errors (e7000_start_remote, (char *) 0,
       "Couldn't establish connection to remote target\n", RETURN_MASK_ALL))
    if (from_tty)
      printf_filtered ("Remote target %s connected to %s\n", target_shortname,
		       dev_name);
}