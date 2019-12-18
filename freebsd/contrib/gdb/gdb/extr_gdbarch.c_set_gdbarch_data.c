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
struct gdbarch_data {size_t index; } ;
struct gdbarch {size_t nr_data; int /*<<< orphan*/ ** data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 

void
set_gdbarch_data (struct gdbarch *gdbarch,
                  struct gdbarch_data *data,
                  void *pointer)
{
  gdb_assert (data->index < gdbarch->nr_data);
  gdb_assert (gdbarch->data[data->index] == NULL);
  gdbarch->data[data->index] = pointer;
}