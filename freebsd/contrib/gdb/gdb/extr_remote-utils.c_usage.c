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
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 

__attribute__((used)) static void
usage (char *proto, char *junk)
{
  if (junk != NULL)
    fprintf_unfiltered (gdb_stderr, "Unrecognized arguments: `%s'.\n", junk);

  error ("Usage: target %s [DEVICE [SPEED [DEBUG]]]\n\
where DEVICE is the name of a device or HOST:PORT", proto);

  return;
}