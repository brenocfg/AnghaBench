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
struct ring_buffer_event {scalar_t__ type_len; int /*<<< orphan*/  time_delta; } ;

/* Variables and functions */
 scalar_t__ RINGBUF_TYPE_PADDING ; 

__attribute__((used)) static inline int rb_null_event(struct ring_buffer_event *event)
{
	return event->type_len == RINGBUF_TYPE_PADDING && !event->time_delta;
}