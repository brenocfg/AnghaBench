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
struct gdbarch {int /*<<< orphan*/  sigtramp_end; } ;
typedef  int /*<<< orphan*/  gdbarch_sigtramp_end_ftype ;

/* Variables and functions */

void
set_gdbarch_sigtramp_end (struct gdbarch *gdbarch,
                          gdbarch_sigtramp_end_ftype sigtramp_end)
{
  gdbarch->sigtramp_end = sigtramp_end;
}