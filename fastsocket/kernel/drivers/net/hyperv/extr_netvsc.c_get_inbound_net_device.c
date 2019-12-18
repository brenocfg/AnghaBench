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
struct netvsc_device {int /*<<< orphan*/  num_outstanding_sends; scalar_t__ destroy; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct netvsc_device* hv_get_drvdata (struct hv_device*) ; 

__attribute__((used)) static struct netvsc_device *get_inbound_net_device(struct hv_device *device)
{
	struct netvsc_device *net_device;

	net_device = hv_get_drvdata(device);

	if (!net_device)
		goto get_in_err;

	if (net_device->destroy &&
		atomic_read(&net_device->num_outstanding_sends) == 0)
		net_device = NULL;

get_in_err:
	return net_device;
}