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
struct gdbarch_data {size_t index; int init_p; void* (* init ) (struct gdbarch*) ;} ;
struct gdbarch {size_t nr_data; void** data; scalar_t__ initialized_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 void* stub1 (struct gdbarch*) ; 

void *
gdbarch_data (struct gdbarch *gdbarch, struct gdbarch_data *data)
{
  gdb_assert (data->index < gdbarch->nr_data);
  /* The data-pointer isn't initialized, call init() to get a value but
     only if the architecture initializaiton has completed.  Otherwise
     punt - hope that the caller knows what they are doing.  */
  if (gdbarch->data[data->index] == NULL
      && gdbarch->initialized_p)
    {
      /* Be careful to detect an initialization cycle.  */
      gdb_assert (data->init_p);
      data->init_p = 0;
      gdb_assert (data->init != NULL);
      gdbarch->data[data->index] = data->init (gdbarch);
      data->init_p = 1;
      gdb_assert (gdbarch->data[data->index] != NULL);
    }
  return gdbarch->data[data->index];
}