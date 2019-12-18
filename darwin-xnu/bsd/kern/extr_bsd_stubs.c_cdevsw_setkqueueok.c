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
typedef  int uint64_t ;
struct cdevsw {int dummy; } ;

/* Variables and functions */
 int CDEVSW_SELECT_KQUEUE ; 
 struct cdevsw* cdevsw ; 
 int* cdevsw_flags ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int nchrdev ; 

int
cdevsw_setkqueueok(int maj, struct cdevsw * csw, int extra_flags)
{
	struct cdevsw * devsw;
	uint64_t flags = CDEVSW_SELECT_KQUEUE;

	if (maj < 0 || maj >= nchrdev) {
		return -1;
	}

	devsw = &cdevsw[maj];
	if ((memcmp((char *)devsw, (char *)csw, sizeof(struct cdevsw)) != 0)) {
		return -1;
	}

	flags |= extra_flags;

	cdevsw_flags[maj] = flags;
	return 0;
}