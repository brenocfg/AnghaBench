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
struct netvsc_device {scalar_t__ destroy; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 struct netvsc_device* hv_get_drvdata (struct hv_device*) ; 

__attribute__((used)) static struct netvsc_device *get_outbound_net_device(struct hv_device *device)
{
	struct netvsc_device *net_device;

	net_device = hv_get_drvdata(device);
	if (net_device && net_device->destroy)
		net_device = NULL;

	return net_device;
}