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
struct format_field {int /*<<< orphan*/  name; struct format_field* next; } ;
struct TYPE_2__ {struct format_field* fields; } ;
struct event_format {TYPE_1__ format; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct format_field *
pevent_find_field(struct event_format *event, const char *name)
{
	struct format_field *format;

	for (format = event->format.fields;
	     format; format = format->next) {
		if (strcmp(format->name, name) == 0)
			break;
	}

	return format;
}