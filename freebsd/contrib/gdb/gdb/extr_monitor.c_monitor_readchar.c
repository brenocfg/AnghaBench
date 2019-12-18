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
 int /*<<< orphan*/  monitor_desc ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int serial_readchar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout ; 

int
monitor_readchar (void)
{
  int c;
  int looping;

  do
    {
      looping = 0;
      c = serial_readchar (monitor_desc, timeout);

      if (c >= 0)
	c &= 0xff;		/* don't lose bit 7 */
    }
  while (looping);

  if (c >= 0)
    return c;

  if (c == SERIAL_TIMEOUT)
    error ("Timeout reading from remote system.");

  perror_with_name ("remote-monitor");
}