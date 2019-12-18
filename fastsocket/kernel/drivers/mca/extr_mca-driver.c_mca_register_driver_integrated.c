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
struct mca_driver {int integrated_id; } ;

/* Variables and functions */
 int mca_register_driver (struct mca_driver*) ; 

int mca_register_driver_integrated(struct mca_driver *mca_driver,
				   int integrated_id)
{
	int r = mca_register_driver(mca_driver);

	if (!r)
		mca_driver->integrated_id = integrated_id;

	return r;
}