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
struct gdbarch {int /*<<< orphan*/  fetch_pointer_argument; } ;
typedef  int /*<<< orphan*/  gdbarch_fetch_pointer_argument_ftype ;

/* Variables and functions */

void
set_gdbarch_fetch_pointer_argument (struct gdbarch *gdbarch,
                                    gdbarch_fetch_pointer_argument_ftype fetch_pointer_argument)
{
  gdbarch->fetch_pointer_argument = fetch_pointer_argument;
}