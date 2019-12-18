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
 int NODEV ; 
 int* chrtoblktab ; 
 int nblkdev ; 
 int nchrdev ; 

int
chrtoblk_set(int cdev, int bdev)
{
	if (cdev >= nchrdev)
		return (-1);
	if (bdev != NODEV && bdev >= nblkdev)
		return (-1);
	chrtoblktab[cdev] = bdev;
	return 0;
}