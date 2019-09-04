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
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int mdFlags; int mdSecsize; } ;

/* Variables and functions */
 int ENXIO ; 
 int NB_MAX_MDEVICES ; 
 int mdInited ; 
 TYPE_1__* mdev ; 
 int minor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static	int mdevsize(dev_t dev) {

	int devid;

	devid = minor(dev);									/* Get minor device number */
	if (devid >= NB_MAX_MDEVICES) return (ENXIO);						/* Not valid */

	if ((mdev[devid].mdFlags & mdInited) == 0) return(-1);		/* Not inited yet */

	return(mdev[devid].mdSecsize);
}