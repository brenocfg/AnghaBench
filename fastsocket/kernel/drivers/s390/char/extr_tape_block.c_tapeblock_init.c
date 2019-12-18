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
 int register_blkdev (int,char*) ; 
 int tapeblock_major ; 

int
tapeblock_init(void)
{
	int rc;

	/* Register the tape major number to the kernel */
	rc = register_blkdev(tapeblock_major, "tBLK");
	if (rc < 0)
		return rc;

	if (tapeblock_major == 0)
		tapeblock_major = rc;
	return 0;
}