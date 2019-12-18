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
struct sctp_ulpevent {int msg_flags; } ;

/* Variables and functions */
 int MSG_NOTIFICATION ; 

int sctp_ulpevent_is_notification(const struct sctp_ulpevent *event)
{
	return MSG_NOTIFICATION == (event->msg_flags & MSG_NOTIFICATION);
}