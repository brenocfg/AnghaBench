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
typedef  size_t guint ;
typedef  scalar_t__ guchar ;
typedef  enum Log_event_type { ____Placeholder_Log_event_type } Log_event_type ;
struct TYPE_2__ {char const* name; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 TYPE_1__* event_type_name ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,int) ; 

const char *network_mysqld_binlog_get_eventname(enum Log_event_type type) {
	static const char *unknown_type = "UNKNOWN";
	guint i;

	for (i = 0; event_type_name[i].name; i++) {
		if ((guchar)event_type_name[i].type == (guchar)type) return event_type_name[i].name;
	}

	g_critical("%s: event-type %d isn't known yet", 
			G_STRLOC,
			type);

	return unknown_type;
}