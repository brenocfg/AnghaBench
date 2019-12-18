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
 struct format_field* pevent_find_common_field (struct event_format*,char const*) ; 
 struct format_field* pevent_find_field (struct event_format*,char const*) ; 

struct format_field *
pevent_find_any_field(struct event_format *event, const char *name)
{
	struct format_field *format;

	format = pevent_find_common_field(event, name);
	if (format)
		return format;
	return pevent_find_field(event, name);
}