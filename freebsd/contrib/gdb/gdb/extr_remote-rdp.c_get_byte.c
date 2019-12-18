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
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  io ; 
 scalar_t__ remote_debug ; 
 int serial_readchar (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ timeout ; 

__attribute__((used)) static unsigned char
get_byte (void)
{
  int c = serial_readchar (io, timeout);

  if (remote_debug)
    fprintf_unfiltered (gdb_stdlog, "[%02x]\n", c);

  if (c == SERIAL_TIMEOUT)
    {
      if (timeout == 0)
	return (unsigned char) c;

      error ("Timeout reading from remote_system");
    }

  return c;
}