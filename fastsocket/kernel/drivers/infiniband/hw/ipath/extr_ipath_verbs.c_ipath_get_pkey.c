#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipath_devdata {TYPE_1__** ipath_pd; } ;
struct TYPE_2__ {unsigned int* port_pkeys; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 

unsigned ipath_get_pkey(struct ipath_devdata *dd, unsigned index)
{
	unsigned ret;

	/* always a kernel port, no locking needed */
	if (index >= ARRAY_SIZE(dd->ipath_pd[0]->port_pkeys))
		ret = 0;
	else
		ret = dd->ipath_pd[0]->port_pkeys[index];

	return ret;
}