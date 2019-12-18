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
struct gdbarch {int /*<<< orphan*/  deprecated_get_saved_register; } ;
typedef  int /*<<< orphan*/  gdbarch_deprecated_get_saved_register_ftype ;

/* Variables and functions */

void
set_gdbarch_deprecated_get_saved_register (struct gdbarch *gdbarch,
                                           gdbarch_deprecated_get_saved_register_ftype deprecated_get_saved_register)
{
  gdbarch->deprecated_get_saved_register = deprecated_get_saved_register;
}