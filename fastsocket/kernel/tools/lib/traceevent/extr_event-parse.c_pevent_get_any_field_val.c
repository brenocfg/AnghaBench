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
struct trace_seq {int dummy; } ;
struct pevent_record {int dummy; } ;
struct format_field {int dummy; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
 int get_field_val (struct trace_seq*,struct format_field*,char const*,struct pevent_record*,unsigned long long*,int) ; 
 struct format_field* pevent_find_any_field (struct event_format*,char const*) ; 

int pevent_get_any_field_val(struct trace_seq *s, struct event_format *event,
			     const char *name, struct pevent_record *record,
			     unsigned long long *val, int err)
{
	struct format_field *field;

	if (!event)
		return -1;

	field = pevent_find_any_field(event, name);

	return get_field_val(s, field, name, record, val, err);
}