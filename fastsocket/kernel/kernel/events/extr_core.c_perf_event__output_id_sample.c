#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct perf_sample_data {int dummy; } ;
struct perf_output_handle {int dummy; } ;
struct TYPE_2__ {scalar_t__ sample_id_all; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_event__output_id_sample (struct perf_output_handle*,struct perf_sample_data*) ; 

void perf_event__output_id_sample(struct perf_event *event,
				  struct perf_output_handle *handle,
				  struct perf_sample_data *sample)
{
	if (event->attr.sample_id_all)
		__perf_event__output_id_sample(handle, sample);
}