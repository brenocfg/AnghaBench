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
struct bmc_device {int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 struct bmc_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int __find_bmc_guid(struct device *dev, void *data)
{
	unsigned char *id = data;
	struct bmc_device *bmc = dev_get_drvdata(dev);
	return memcmp(bmc->guid, id, 16) == 0;
}