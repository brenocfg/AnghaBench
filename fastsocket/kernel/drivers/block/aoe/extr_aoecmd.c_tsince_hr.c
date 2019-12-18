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
typedef  int u32 ;
struct timeval {int tv_usec; int tv_sec; } ;
struct TYPE_2__ {int tv_usec; int tv_sec; } ;
struct frame {int sent_jiffs; TYPE_1__ sent; } ;

/* Variables and functions */
 int HZ ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static int
tsince_hr(struct frame *f)
{
	struct timeval now;
	int n;

	do_gettimeofday(&now);
	n = now.tv_usec - f->sent.tv_usec;
	n += (now.tv_sec - f->sent.tv_sec) * USEC_PER_SEC;

	if (n < 0)
		n = -n;

	/* For relatively long periods, use jiffies to avoid
	 * discrepancies caused by updates to the system time.
	 *
	 * On system with HZ of 1000, 32-bits is over 49 days
	 * worth of jiffies, or over 71 minutes worth of usecs.
	 *
	 * Jiffies overflow is handled by subtraction of unsigned ints:
	 * (gdb) print (unsigned) 2 - (unsigned) 0xfffffffe
	 * $3 = 4
	 * (gdb)
	 */
	if (n > USEC_PER_SEC / 4) {
		n = ((u32) jiffies) - f->sent_jiffs;
		n *= USEC_PER_SEC / HZ;
	}

	return n;
}