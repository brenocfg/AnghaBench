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

/* Variables and functions */
 int DRQ_STAT ; 
 int /*<<< orphan*/  HD_STATUS ; 
 int /*<<< orphan*/  dump_status (char*,int) ; 
 int inb_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wait_DRQ(void)
{
	int retries;
	int stat;

	for (retries = 0; retries < 100000; retries++) {
		stat = inb_p(HD_STATUS);
		if (stat & DRQ_STAT)
			return 0;
	}
	dump_status("wait_DRQ", stat);
	return -1;
}