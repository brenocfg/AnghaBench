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
struct event_format {int dummy; } ;
typedef  enum pevent_errno { ____Placeholder_pevent_errno } pevent_errno ;

/* Variables and functions */
 int __pevent_parse_format (struct event_format**,int /*<<< orphan*/ *,char const*,unsigned long,char const*) ; 

enum pevent_errno pevent_parse_format(struct event_format **eventp, const char *buf,
				      unsigned long size, const char *sys)
{
	return __pevent_parse_format(eventp, NULL, buf, size, sys);
}