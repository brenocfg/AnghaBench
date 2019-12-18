#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {TYPE_1__* context; } ;
struct pebs_tracer {TYPE_2__ ds; } ;
struct TYPE_6__ {unsigned int nr_counter_reset; int sizeof_ptr_field; } ;
struct TYPE_4__ {scalar_t__ ds; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_DS_PTR_FIELDS ; 
 unsigned int PEBS_RESET_FIELD_SIZE ; 
 TYPE_3__ ds_cfg ; 

int ds_set_pebs_reset(struct pebs_tracer *tracer,
		      unsigned int counter, u64 value)
{
	if (!tracer)
		return -EINVAL;

	if (ds_cfg.nr_counter_reset < counter)
		return -EINVAL;

	*(u64 *)(tracer->ds.context->ds +
		 (NUM_DS_PTR_FIELDS * ds_cfg.sizeof_ptr_field) +
		 (counter * PEBS_RESET_FIELD_SIZE)) = value;

	return 0;
}