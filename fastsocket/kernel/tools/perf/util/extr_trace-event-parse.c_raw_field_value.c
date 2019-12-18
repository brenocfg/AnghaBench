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
struct format_field {int dummy; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
 struct format_field* pevent_find_any_field (struct event_format*,char const*) ; 
 int /*<<< orphan*/  pevent_read_number_field (struct format_field*,void*,unsigned long long*) ; 

unsigned long long
raw_field_value(struct event_format *event, const char *name, void *data)
{
	struct format_field *field;
	unsigned long long val;

	field = pevent_find_any_field(event, name);
	if (!field)
		return 0ULL;

	pevent_read_number_field(field, data, &val);

	return val;
}