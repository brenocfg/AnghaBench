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
struct tty_struct {struct stliport* driver_data; } ;
struct stliport {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ST_TXBUSY ; 
 int /*<<< orphan*/  current ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (int,unsigned long) ; 

__attribute__((used)) static void stli_waituntilsent(struct tty_struct *tty, int timeout)
{
	struct stliport *portp;
	unsigned long tend;

	portp = tty->driver_data;
	if (portp == NULL)
		return;

	if (timeout == 0)
		timeout = HZ;
	tend = jiffies + timeout;

	while (test_bit(ST_TXBUSY, &portp->state)) {
		if (signal_pending(current))
			break;
		msleep_interruptible(20);
		if (time_after_eq(jiffies, tend))
			break;
	}
}