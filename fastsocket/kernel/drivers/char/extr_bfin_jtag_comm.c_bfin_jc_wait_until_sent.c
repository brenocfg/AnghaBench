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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfin_jc_write_buf ; 
 int /*<<< orphan*/  circ_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int jiffies ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static void
bfin_jc_wait_until_sent(struct tty_struct *tty, int timeout)
{
	unsigned long expire = jiffies + timeout;
	while (!circ_empty(&bfin_jc_write_buf)) {
		if (signal_pending(current))
			break;
		if (time_after(jiffies, expire))
			break;
	}
}