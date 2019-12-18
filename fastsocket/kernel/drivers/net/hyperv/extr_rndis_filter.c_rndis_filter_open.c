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
struct netvsc_device {int /*<<< orphan*/  extension; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct netvsc_device* hv_get_drvdata (struct hv_device*) ; 
 int rndis_filter_open_device (int /*<<< orphan*/ ) ; 

int rndis_filter_open(struct hv_device *dev)
{
	struct netvsc_device *net_device = hv_get_drvdata(dev);

	if (!net_device)
		return -EINVAL;

	return rndis_filter_open_device(net_device->extension);
}