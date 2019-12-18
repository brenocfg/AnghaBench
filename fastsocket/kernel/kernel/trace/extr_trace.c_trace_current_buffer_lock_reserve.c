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
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct TYPE_2__ {struct ring_buffer* buffer; } ;

/* Variables and functions */
 TYPE_1__ global_trace ; 
 struct ring_buffer_event* trace_buffer_lock_reserve (struct ring_buffer*,int,unsigned long,unsigned long,int) ; 

struct ring_buffer_event *
trace_current_buffer_lock_reserve(struct ring_buffer **current_rb,
				  int type, unsigned long len,
				  unsigned long flags, int pc)
{
	*current_rb = global_trace.buffer;
	return trace_buffer_lock_reserve(*current_rb,
					 type, len, flags, pc);
}