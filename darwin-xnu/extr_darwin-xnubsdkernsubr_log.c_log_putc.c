#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int msg_bufx; int msg_bufr; int msg_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_LOCK () ; 
 int /*<<< orphan*/  LOG_UNLOCK () ; 
 int /*<<< orphan*/  log_putc_locked (TYPE_1__*,char) ; 
 int /*<<< orphan*/  logwakeup (TYPE_1__*) ; 
 TYPE_1__* msgbufp ; 

void
log_putc(char c)
{
	int unread_count = 0;
	LOG_LOCK();
	log_putc_locked(msgbufp, c);
	unread_count = msgbufp->msg_bufx - msgbufp->msg_bufr;
	LOG_UNLOCK();

	if (unread_count < 0)
		unread_count = 0 - unread_count;
	if (c == '\n' || unread_count >= (msgbufp->msg_size / 2))
		logwakeup(msgbufp);
}