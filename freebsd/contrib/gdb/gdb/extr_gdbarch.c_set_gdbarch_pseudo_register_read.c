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
struct gdbarch {int /*<<< orphan*/  pseudo_register_read; } ;
typedef  int /*<<< orphan*/  gdbarch_pseudo_register_read_ftype ;

/* Variables and functions */

void
set_gdbarch_pseudo_register_read (struct gdbarch *gdbarch,
                                  gdbarch_pseudo_register_read_ftype pseudo_register_read)
{
  gdbarch->pseudo_register_read = pseudo_register_read;
}