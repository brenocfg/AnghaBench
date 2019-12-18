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
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static void
go32_attach (char *args, int from_tty)
{
  error ("\
You cannot attach to a running program on this platform.\n\
Use the `run' command to run DJGPP programs.");
}