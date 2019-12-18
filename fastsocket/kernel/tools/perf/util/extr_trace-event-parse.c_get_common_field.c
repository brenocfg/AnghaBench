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
struct scripting_context {scalar_t__ event_data; struct pevent* pevent; } ;
struct pevent {struct event_format** events; } ;
struct format_field {int offset; int size; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
 struct format_field* pevent_find_common_field (struct event_format*,char const*) ; 
 int pevent_read_number (struct pevent*,scalar_t__,int) ; 

__attribute__((used)) static int get_common_field(struct scripting_context *context,
			    int *offset, int *size, const char *type)
{
	struct pevent *pevent = context->pevent;
	struct event_format *event;
	struct format_field *field;

	if (!*size) {
		if (!pevent->events)
			return 0;

		event = pevent->events[0];
		field = pevent_find_common_field(event, type);
		if (!field)
			return 0;
		*offset = field->offset;
		*size = field->size;
	}

	return pevent_read_number(pevent, context->event_data + *offset, *size);
}