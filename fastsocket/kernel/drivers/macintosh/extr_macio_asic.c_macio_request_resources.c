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
struct macio_dev {int n_resources; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  macio_release_resource (struct macio_dev*,int) ; 
 scalar_t__ macio_request_resource (struct macio_dev*,int,char const*) ; 

int macio_request_resources(struct macio_dev *dev, const char *name)
{
	int i;
	
	for (i = 0; i < dev->n_resources; i++)
		if (macio_request_resource(dev, i, name))
			goto err_out;
	return 0;

err_out:
	while(--i >= 0)
		macio_release_resource(dev, i);
		
	return -EBUSY;
}