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
struct umc_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct umc_dev*) ; 
 struct umc_dev* to_umc_dev (struct device*) ; 

__attribute__((used)) static void umc_device_release(struct device *dev)
{
	struct umc_dev *umc = to_umc_dev(dev);

	kfree(umc);
}