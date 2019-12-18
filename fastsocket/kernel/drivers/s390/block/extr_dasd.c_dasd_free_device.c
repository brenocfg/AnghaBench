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
struct dasd_device {scalar_t__ ccw_mem; scalar_t__ erp_mem; struct dasd_device* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  kfree (struct dasd_device*) ; 

void dasd_free_device(struct dasd_device *device)
{
	kfree(device->private);
	free_page((unsigned long) device->erp_mem);
	free_pages((unsigned long) device->ccw_mem, 1);
	kfree(device);
}