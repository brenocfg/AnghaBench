#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  scalar_t__ dev_t ;
struct TYPE_4__ {scalar_t__ dev; struct TYPE_4__* fow; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ DEVT ;

/* Variables and functions */
 unsigned int D_TAB_SZ ; 
 TYPE_1__** dtab ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 

__attribute__((used)) static DEVT *
chk_dev(dev_t dev, int add)
{
	DEVT *pt;
	u_int indx;

	if (dtab == NULL)
		return(NULL);
	/*
	 * look to see if this device is already in the table
	 */
	indx = ((unsigned)dev) % D_TAB_SZ;
	if ((pt = dtab[indx]) != NULL) {
		while ((pt != NULL) && (pt->dev != dev))
			pt = pt->fow;

		/*
		 * found it, return a pointer to it
		 */
		if (pt != NULL)
			return(pt);
	}

	/*
	 * not in table, we add it only if told to as this may just be a check
	 * to see if a device number is being used.
	 */
	if (add == 0)
		return(NULL);

	/*
	 * allocate a node for this device and add it to the front of the hash
	 * chain. Note we do not assign remaps values here, so the pt->list
	 * list must be NULL.
	 */
	if ((pt = (DEVT *)malloc(sizeof(DEVT))) == NULL) {
		paxwarn(1, "Device map table out of memory");
		return(NULL);
	}
	pt->dev = dev;
	pt->list = NULL;
	pt->fow = dtab[indx];
	dtab[indx] = pt;
	return(pt);
}