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
struct TYPE_2__ {int mdFlags; scalar_t__ mdcdevb; scalar_t__ mdbdevb; scalar_t__ mdCDev; scalar_t__ mdBDev; scalar_t__ mdSecsize; scalar_t__ mdSize; scalar_t__ mdBase; } ;

/* Variables and functions */
 int NB_MAX_MDEVICES ; 
 int /*<<< orphan*/  devfs_remove (scalar_t__) ; 
 int mdInited ; 
 TYPE_1__* mdev ; 

void mdevremoveall(void) {

	int i;

	for(i = 0; i < NB_MAX_MDEVICES; i++) {
		if(!(mdev[i].mdFlags & mdInited)) continue;	/* Ignore unused mdevs */

		devfs_remove(mdev[i].mdbdevb);			/* Remove the block device */
		devfs_remove(mdev[i].mdcdevb);			/* Remove the character device */

		mdev[i].mdBase = 0;				/* Clear the mdev's storage */
		mdev[i].mdSize = 0;
		mdev[i].mdSecsize = 0;
		mdev[i].mdFlags = 0;
		mdev[i].mdBDev = 0;
		mdev[i].mdCDev = 0;
		mdev[i].mdbdevb = 0;
		mdev[i].mdcdevb = 0;
	}
}