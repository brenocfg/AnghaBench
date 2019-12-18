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
struct TYPE_2__ {int tv_usec; scalar_t__ tv_sec; } ;
struct itimerval {TYPE_1__ it_value; TYPE_1__ it_interval; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_spinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_spinunlock (int /*<<< orphan*/ ) ; 
 scalar_t__ timerisset (TYPE_1__*) ; 

int
itimerdecr(proc_t p,
	struct itimerval *itp, int usec)
{

	proc_spinlock(p);
	
	if (itp->it_value.tv_usec < usec) {
		if (itp->it_value.tv_sec == 0) {
			/* expired, and already in next interval */
			usec -= itp->it_value.tv_usec;
			goto expire;
		}
		itp->it_value.tv_usec += 1000000;
		itp->it_value.tv_sec--;
	}
	itp->it_value.tv_usec -= usec;
	usec = 0;
	if (timerisset(&itp->it_value)) {
		proc_spinunlock(p);
		return (1);
	}
	/* expired, exactly at end of interval */
expire:
	if (timerisset(&itp->it_interval)) {
		itp->it_value = itp->it_interval;
		if (itp->it_value.tv_sec > 0) {
		itp->it_value.tv_usec -= usec;
		if (itp->it_value.tv_usec < 0) {
			itp->it_value.tv_usec += 1000000;
			itp->it_value.tv_sec--;
			}
		}
	} else
		itp->it_value.tv_usec = 0;		/* sec is already 0 */
	proc_spinunlock(p);
	return (0);
}