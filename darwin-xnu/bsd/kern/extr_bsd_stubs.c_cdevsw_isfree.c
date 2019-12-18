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
struct cdevsw {int dummy; } ;

/* Variables and functions */
 struct cdevsw* cdevsw ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int nchrdev ; 
 int /*<<< orphan*/  nocdev ; 

int
cdevsw_isfree(int index)
{
	struct cdevsw * devsw;

	if (index < 0) {
		if (index == -1)
			index = 0;
		else
			index = -index; /* start at least this far up in the table */
		devsw = &cdevsw[index];
		for (; index < nchrdev; index++, devsw++) {
			if (memcmp((char *)devsw, (char *)&nocdev, sizeof(struct cdevsw)) == 0)
				break;
		}
	}

	if (index < 0 || index >= nchrdev)
		return (-1);

	devsw = &cdevsw[index];
	if ((memcmp((char *)devsw, (char *)&nocdev, sizeof(struct cdevsw)) != 0)) {
		return (-1);
	}
	return (index);
}