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
struct sst25l_flash {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long MAX_READY_WAIT_JIFFIES ; 
 int SST25L_STATUS_BUSY ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long jiffies ; 
 int sst25l_status (struct sst25l_flash*,int*) ; 
 int /*<<< orphan*/  time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int sst25l_wait_till_ready(struct sst25l_flash *flash)
{
	unsigned long deadline;
	int status, err;

	deadline = jiffies + MAX_READY_WAIT_JIFFIES;
	do {
		err = sst25l_status(flash, &status);
		if (err)
			return err;
		if (!(status & SST25L_STATUS_BUSY))
			return 0;

		cond_resched();
	} while (!time_after_eq(jiffies, deadline));

	return -ETIMEDOUT;
}