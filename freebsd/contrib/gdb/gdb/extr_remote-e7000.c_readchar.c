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
 int /*<<< orphan*/  e7000_desc ; 
 scalar_t__ echo ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int normal (int) ; 
 int /*<<< orphan*/  putchar_unfiltered (int) ; 
 scalar_t__ remote_debug ; 
 int serial_readchar (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
readchar (int timeout)
{
  int c;

  do
    {
      c = serial_readchar (e7000_desc, timeout);
    }
  while (c > 127);

  if (c == SERIAL_TIMEOUT)
    {
      if (timeout == 0)
	return -1;
      echo = 0;
      error ("Timeout reading from remote system.");
    }
  else if (c < 0)
    error ("Serial communication error");

  if (remote_debug)
    {
      putchar_unfiltered (c);
      gdb_flush (gdb_stdout);
    }

  return normal (c);
}