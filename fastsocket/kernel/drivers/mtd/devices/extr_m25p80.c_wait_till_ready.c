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
struct m25p {int dummy; } ;

/* Variables and functions */
 unsigned long MAX_READY_WAIT_JIFFIES ; 
 int SR_WIP ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long jiffies ; 
 int read_sr (struct m25p*) ; 
 int /*<<< orphan*/  time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int wait_till_ready(struct m25p *flash)
{
	unsigned long deadline;
	int sr;

	deadline = jiffies + MAX_READY_WAIT_JIFFIES;

	do {
		if ((sr = read_sr(flash)) < 0)
			break;
		else if (!(sr & SR_WIP))
			return 0;

		cond_resched();

	} while (!time_after_eq(jiffies, deadline));

	return 1;
}