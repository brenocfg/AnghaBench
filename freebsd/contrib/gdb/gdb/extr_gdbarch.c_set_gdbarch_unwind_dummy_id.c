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
struct gdbarch {int /*<<< orphan*/  unwind_dummy_id; } ;
typedef  int /*<<< orphan*/  gdbarch_unwind_dummy_id_ftype ;

/* Variables and functions */

void
set_gdbarch_unwind_dummy_id (struct gdbarch *gdbarch,
                             gdbarch_unwind_dummy_id_ftype unwind_dummy_id)
{
  gdbarch->unwind_dummy_id = unwind_dummy_id;
}