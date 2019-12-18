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
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  io ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
put_byte (char val)
{
  if (remote_debug)
    fprintf_unfiltered (gdb_stdlog, "(%02x)\n", val);
  serial_write (io, &val, 1);
}