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
struct pevent_record {int dummy; } ;
struct pevent {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 TYPE_1__* cpu_data ; 
 struct pevent_record* trace_peek_data (struct pevent*,int) ; 

struct pevent_record *trace_read_data(struct pevent *pevent, int cpu)
{
	struct pevent_record *data;

	data = trace_peek_data(pevent, cpu);
	cpu_data[cpu].next = NULL;

	return data;
}