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
struct device {int dummy; } ;
struct ap_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ap_device*) ; 
 struct ap_device* to_ap_dev (struct device*) ; 

__attribute__((used)) static void ap_device_release(struct device *dev)
{
	struct ap_device *ap_dev = to_ap_dev(dev);

	kfree(ap_dev);
}