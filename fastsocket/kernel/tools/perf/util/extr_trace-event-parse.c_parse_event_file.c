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
struct pevent {int dummy; } ;

/* Variables and functions */
 int pevent_parse_event (struct pevent*,char*,unsigned long,char*) ; 

int parse_event_file(struct pevent *pevent,
		     char *buf, unsigned long size, char *sys)
{
	return pevent_parse_event(pevent, buf, size, sys);
}