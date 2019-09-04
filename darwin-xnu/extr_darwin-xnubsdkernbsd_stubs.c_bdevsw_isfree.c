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
struct bdevsw {int dummy; } ;

/* Variables and functions */
 struct bdevsw* bdevsw ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int nblkdev ; 
 int /*<<< orphan*/  nobdev ; 

int
bdevsw_isfree(int index)
{
	struct bdevsw * devsw;

	if (index < 0) {
		if (index == -1)
			index = 1; /* start at 1 to avoid collision with volfs (Radar 2842228) */
		else
			index = -index; /* start at least this far up in the table */
		devsw = &bdevsw[index];
		for (; index < nblkdev; index++, devsw++) {
			if (memcmp((char *)devsw, (char *)&nobdev, sizeof(struct bdevsw)) == 0)
				break;
		}
	}

	if (index < 0 || index >= nblkdev)
		return (-1);

	devsw = &bdevsw[index];
	if ((memcmp((char *)devsw, (char *)&nobdev, sizeof(struct bdevsw)) != 0)) {
		return (-1);
	}
	return (index);
}