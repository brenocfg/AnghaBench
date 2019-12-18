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
struct gdbarch {int /*<<< orphan*/  address_class_type_flags_to_name; } ;
typedef  int /*<<< orphan*/  gdbarch_address_class_type_flags_to_name_ftype ;

/* Variables and functions */

void
set_gdbarch_address_class_type_flags_to_name (struct gdbarch *gdbarch,
                                              gdbarch_address_class_type_flags_to_name_ftype address_class_type_flags_to_name)
{
  gdbarch->address_class_type_flags_to_name = address_class_type_flags_to_name;
}