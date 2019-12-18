#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pevent_record {char* data; } ;
struct pevent {int dummy; } ;
struct TYPE_3__ {char* buffer; TYPE_2__* field; } ;
struct filter_arg {TYPE_1__ str; } ;
struct event_format {struct pevent* pevent; } ;
struct TYPE_4__ {int flags; int offset; int size; struct event_format* event; } ;

/* Variables and functions */
 int FIELD_IS_LONG ; 
 int FIELD_IS_POINTER ; 
 int FIELD_IS_STRING ; 
 unsigned long long get_value (struct event_format*,TYPE_2__*,struct pevent_record*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* pevent_find_function (struct pevent*,unsigned long long) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long) ; 

__attribute__((used)) static const char *get_field_str(struct filter_arg *arg, struct pevent_record *record)
{
	struct event_format *event;
	struct pevent *pevent;
	unsigned long long addr;
	const char *val = NULL;
	char hex[64];

	/* If the field is not a string convert it */
	if (arg->str.field->flags & FIELD_IS_STRING) {
		val = record->data + arg->str.field->offset;

		/*
		 * We need to copy the data since we can't be sure the field
		 * is null terminated.
		 */
		if (*(val + arg->str.field->size - 1)) {
			/* copy it */
			memcpy(arg->str.buffer, val, arg->str.field->size);
			/* the buffer is already NULL terminated */
			val = arg->str.buffer;
		}

	} else {
		event = arg->str.field->event;
		pevent = event->pevent;
		addr = get_value(event, arg->str.field, record);

		if (arg->str.field->flags & (FIELD_IS_POINTER | FIELD_IS_LONG))
			/* convert to a kernel symbol */
			val = pevent_find_function(pevent, addr);

		if (val == NULL) {
			/* just use the hex of the string name */
			snprintf(hex, 64, "0x%llx", addr);
			val = hex;
		}
	}

	return val;
}