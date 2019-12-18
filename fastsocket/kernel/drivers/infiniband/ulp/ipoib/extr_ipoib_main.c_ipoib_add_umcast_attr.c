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
struct net_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_umcast ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ipoib_add_umcast_attr(struct net_device *dev)
{
	return device_create_file(&dev->dev, &dev_attr_umcast);
}