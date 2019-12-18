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
typedef  int dev_t ;
struct TYPE_2__ {int mdFlags; int mdBDev; } ;

/* Variables and functions */
 int NB_MAX_MDEVICES ; 
 int mdInited ; 
 TYPE_1__* mdev ; 

dev_t mdevlookup(int devid) {
	
	if((devid < 0) || (devid >= NB_MAX_MDEVICES)) return -1;			/* Filter any bogus requests */
	if(!(mdev[devid].mdFlags & mdInited)) return -1;	/* This one hasn't been defined */
	return mdev[devid].mdBDev;							/* Return the device number */
}