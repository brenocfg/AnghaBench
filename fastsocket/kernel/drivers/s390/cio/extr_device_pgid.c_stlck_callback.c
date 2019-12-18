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
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_device_stlck_done (struct ccw_device*,void*,int) ; 

__attribute__((used)) static void stlck_callback(struct ccw_device *cdev, void *data, int rc)
{
	ccw_device_stlck_done(cdev, data, rc);
}