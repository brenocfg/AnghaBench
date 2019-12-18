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
struct trace_seq {int dummy; } ;
struct format_field {unsigned long long name; int flags; unsigned int offset; unsigned int size; struct format_field* next; } ;
struct TYPE_2__ {struct format_field* fields; } ;
struct event_format {int /*<<< orphan*/  pevent; TYPE_1__ format; } ;

/* Variables and functions */
 int FIELD_IS_ARRAY ; 
 int FIELD_IS_DYNAMIC ; 
 int FIELD_IS_LONG ; 
 int FIELD_IS_POINTER ; 
 int FIELD_IS_SIGNED ; 
 int FIELD_IS_STRING ; 
 scalar_t__ is_printable_array (void*,unsigned int) ; 
 unsigned long long pevent_read_number (int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static void print_event_fields(struct trace_seq *s, void *data, int size,
			       struct event_format *event)
{
	struct format_field *field;
	unsigned long long val;
	unsigned int offset, len, i;

	field = event->format.fields;
	while (field) {
		trace_seq_printf(s, " %s=", field->name);
		if (field->flags & FIELD_IS_ARRAY) {
			offset = field->offset;
			len = field->size;
			if (field->flags & FIELD_IS_DYNAMIC) {
				val = pevent_read_number(event->pevent, data + offset, len);
				offset = val;
				len = offset >> 16;
				offset &= 0xffff;
			}
			if (field->flags & FIELD_IS_STRING &&
			    is_printable_array(data + offset, len)) {
				trace_seq_printf(s, "%s", (char *)data + offset);
			} else {
				trace_seq_puts(s, "ARRAY[");
				for (i = 0; i < len; i++) {
					if (i)
						trace_seq_puts(s, ", ");
					trace_seq_printf(s, "%02x",
							 *((unsigned char *)data + offset + i));
				}
				trace_seq_putc(s, ']');
				field->flags &= ~FIELD_IS_STRING;
			}
		} else {
			val = pevent_read_number(event->pevent, data + field->offset,
						 field->size);
			if (field->flags & FIELD_IS_POINTER) {
				trace_seq_printf(s, "0x%llx", val);
			} else if (field->flags & FIELD_IS_SIGNED) {
				switch (field->size) {
				case 4:
					/*
					 * If field is long then print it in hex.
					 * A long usually stores pointers.
					 */
					if (field->flags & FIELD_IS_LONG)
						trace_seq_printf(s, "0x%x", (int)val);
					else
						trace_seq_printf(s, "%d", (int)val);
					break;
				case 2:
					trace_seq_printf(s, "%2d", (short)val);
					break;
				case 1:
					trace_seq_printf(s, "%1d", (char)val);
					break;
				default:
					trace_seq_printf(s, "%lld", val);
				}
			} else {
				if (field->flags & FIELD_IS_LONG)
					trace_seq_printf(s, "0x%llx", val);
				else
					trace_seq_printf(s, "%llu", val);
			}
		}
		field = field->next;
	}
}