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
struct gdbarch {int /*<<< orphan*/  construct_inferior_arguments; } ;
typedef  int /*<<< orphan*/  gdbarch_construct_inferior_arguments_ftype ;

/* Variables and functions */

void
set_gdbarch_construct_inferior_arguments (struct gdbarch *gdbarch,
                                          gdbarch_construct_inferior_arguments_ftype construct_inferior_arguments)
{
  gdbarch->construct_inferior_arguments = construct_inferior_arguments;
}