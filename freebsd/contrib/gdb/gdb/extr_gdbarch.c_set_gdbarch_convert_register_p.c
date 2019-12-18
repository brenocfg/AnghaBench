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
struct gdbarch {int /*<<< orphan*/  convert_register_p; } ;
typedef  int /*<<< orphan*/  gdbarch_convert_register_p_ftype ;

/* Variables and functions */

void
set_gdbarch_convert_register_p (struct gdbarch *gdbarch,
                                gdbarch_convert_register_p_ftype convert_register_p)
{
  gdbarch->convert_register_p = convert_register_p;
}