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
struct gdbarch {int /*<<< orphan*/  get_longjmp_target; } ;
typedef  int /*<<< orphan*/  gdbarch_get_longjmp_target_ftype ;

/* Variables and functions */

void
set_gdbarch_get_longjmp_target (struct gdbarch *gdbarch,
                                gdbarch_get_longjmp_target_ftype get_longjmp_target)
{
  gdbarch->get_longjmp_target = get_longjmp_target;
}