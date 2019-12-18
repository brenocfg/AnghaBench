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
struct ring_buffer_event {unsigned int type_len; unsigned int* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ALIGNMENT ; 
 unsigned int RB_EVNT_HDR_SIZE ; 
 unsigned int RB_MAX_SMALL_DATA ; 
#define  RINGBUF_TYPE_PADDING 130 
#define  RINGBUF_TYPE_TIME_EXTEND 129 
#define  RINGBUF_TYPE_TIME_STAMP 128 

__attribute__((used)) static void
rb_update_event(struct ring_buffer_event *event,
			 unsigned type, unsigned length)
{
	event->type_len = type;

	switch (type) {

	case RINGBUF_TYPE_PADDING:
	case RINGBUF_TYPE_TIME_EXTEND:
	case RINGBUF_TYPE_TIME_STAMP:
		break;

	case 0:
		length -= RB_EVNT_HDR_SIZE;
		if (length > RB_MAX_SMALL_DATA)
			event->array[0] = length;
		else
			event->type_len = DIV_ROUND_UP(length, RB_ALIGNMENT);
		break;
	default:
		BUG();
	}
}