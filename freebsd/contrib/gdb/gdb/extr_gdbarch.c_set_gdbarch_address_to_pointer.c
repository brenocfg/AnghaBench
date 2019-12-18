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
struct gdbarch {int /*<<< orphan*/  address_to_pointer; } ;
typedef  int /*<<< orphan*/  gdbarch_address_to_pointer_ftype ;

/* Variables and functions */

void
set_gdbarch_address_to_pointer (struct gdbarch *gdbarch,
                                gdbarch_address_to_pointer_ftype address_to_pointer)
{
  gdbarch->address_to_pointer = address_to_pointer;
}