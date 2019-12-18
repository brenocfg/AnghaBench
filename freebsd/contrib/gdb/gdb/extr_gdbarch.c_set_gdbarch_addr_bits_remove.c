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
struct gdbarch {int /*<<< orphan*/  addr_bits_remove; } ;
typedef  int /*<<< orphan*/  gdbarch_addr_bits_remove_ftype ;

/* Variables and functions */

void
set_gdbarch_addr_bits_remove (struct gdbarch *gdbarch,
                              gdbarch_addr_bits_remove_ftype addr_bits_remove)
{
  gdbarch->addr_bits_remove = addr_bits_remove;
}