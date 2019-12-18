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
 int SERIAL_TIMEOUT ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  log_file ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ ) ; 
 int serial_readchar (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st2000_desc ; 

__attribute__((used)) static int
readchar (int timeout)
{
  int c;

  c = serial_readchar (st2000_desc, timeout);

#ifdef LOG_FILE
  putc (c & 0x7f, log_file);
#endif

  if (c >= 0)
    return c & 0x7f;

  if (c == SERIAL_TIMEOUT)
    {
      if (timeout == 0)
	return c;		/* Polls shouldn't generate timeout errors */

      error ("Timeout reading from remote system.");
    }

  perror_with_name ("remote-st2000");
}