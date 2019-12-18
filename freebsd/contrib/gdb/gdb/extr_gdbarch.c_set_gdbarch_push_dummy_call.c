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
struct gdbarch {int /*<<< orphan*/  push_dummy_call; } ;
typedef  int /*<<< orphan*/  gdbarch_push_dummy_call_ftype ;

/* Variables and functions */

void
set_gdbarch_push_dummy_call (struct gdbarch *gdbarch,
                             gdbarch_push_dummy_call_ftype push_dummy_call)
{
  gdbarch->push_dummy_call = push_dummy_call;
}