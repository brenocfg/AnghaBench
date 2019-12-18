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
struct gdbarch {int /*<<< orphan*/  stabs_argument_has_addr; } ;
typedef  int /*<<< orphan*/  gdbarch_stabs_argument_has_addr_ftype ;

/* Variables and functions */

void
set_gdbarch_stabs_argument_has_addr (struct gdbarch *gdbarch,
                                     gdbarch_stabs_argument_has_addr_ftype stabs_argument_has_addr)
{
  gdbarch->stabs_argument_has_addr = stabs_argument_has_addr;
}