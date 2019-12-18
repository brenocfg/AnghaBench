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
 int /*<<< orphan*/  e7000_desc ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expect (char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  safe_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  using_pc ; 

__attribute__((used)) static void
puts_e7000debug (char *buf)
{
  if (!e7000_desc)
    error ("Use \"target e7000 ...\" first.");

  if (remote_debug)
    printf_unfiltered ("Sending %s\n", buf);

  if (serial_write (e7000_desc, buf, strlen (buf)))
    fprintf_unfiltered (gdb_stderr, "serial_write failed: %s\n", safe_strerror (errno));

  /* And expect to see it echoed, unless using the pc interface */
#if 0
  if (!using_pc)
#endif
    expect (buf);
}