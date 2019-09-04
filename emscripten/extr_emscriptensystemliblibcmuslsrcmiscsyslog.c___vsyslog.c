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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ ) ; 
 int LOG_MASK (int) ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _vsyslog (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 int log_mask ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 

void __vsyslog(int priority, const char *message, va_list ap)
{
	int cs;
	if (!(log_mask & LOG_MASK(priority&7)) || (priority&~0x3ff)) return;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	LOCK(lock);
	_vsyslog(priority, message, ap);
	UNLOCK(lock);
	pthread_setcancelstate(cs, 0);
}