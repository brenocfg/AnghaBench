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
struct gdbarch {int /*<<< orphan*/  deprecated_register_convert_to_raw; } ;
typedef  int /*<<< orphan*/  gdbarch_deprecated_register_convert_to_raw_ftype ;

/* Variables and functions */

void
set_gdbarch_deprecated_register_convert_to_raw (struct gdbarch *gdbarch,
                                                gdbarch_deprecated_register_convert_to_raw_ftype deprecated_register_convert_to_raw)
{
  gdbarch->deprecated_register_convert_to_raw = deprecated_register_convert_to_raw;
}