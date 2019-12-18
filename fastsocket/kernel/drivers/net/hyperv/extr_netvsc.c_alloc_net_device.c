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
struct netvsc_device {int start_remove; int destroy; struct net_device* ndev; struct hv_device* dev; int /*<<< orphan*/  wait_drain; } ;
struct net_device {int dummy; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct net_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,struct netvsc_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct netvsc_device* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct netvsc_device *alloc_net_device(struct hv_device *device)
{
	struct netvsc_device *net_device;
	struct net_device *ndev = hv_get_drvdata(device);

	net_device = kzalloc(sizeof(struct netvsc_device), GFP_KERNEL);
	if (!net_device)
		return NULL;

	init_waitqueue_head(&net_device->wait_drain);
	net_device->start_remove = false;
	net_device->destroy = false;
	net_device->dev = device;
	net_device->ndev = ndev;

	hv_set_drvdata(device, net_device);
	return net_device;
}