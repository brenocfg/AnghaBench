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
 unsigned char BUSY_STAT ; 
 int /*<<< orphan*/  HD_STATUS ; 
 unsigned char READY_STAT ; 
 unsigned char SEEK_STAT ; 
 unsigned char STAT_OK ; 
 int /*<<< orphan*/  dump_status (char*,unsigned char) ; 
 unsigned char inb_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drive_busy(void)
{
	unsigned int i;
	unsigned char c;

	for (i = 0; i < 500000 ; i++) {
		c = inb_p(HD_STATUS);
		if ((c & (BUSY_STAT | READY_STAT | SEEK_STAT)) == STAT_OK)
			return 0;
	}
	dump_status("reset timed out", c);
	return 1;
}