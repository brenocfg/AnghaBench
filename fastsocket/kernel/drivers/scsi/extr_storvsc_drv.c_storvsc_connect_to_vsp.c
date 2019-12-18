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
typedef  int /*<<< orphan*/  u32 ;
struct vmstorage_channel_properties {int dummy; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vmstorage_channel_properties*,int /*<<< orphan*/ ,int) ; 
 int storvsc_channel_init (struct hv_device*) ; 
 int /*<<< orphan*/  storvsc_on_channel_callback ; 
 int vmbus_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int storvsc_connect_to_vsp(struct hv_device *device, u32 ring_size)
{
	struct vmstorage_channel_properties props;
	int ret;

	memset(&props, 0, sizeof(struct vmstorage_channel_properties));

	ret = vmbus_open(device->channel,
			 ring_size,
			 ring_size,
			 (void *)&props,
			 sizeof(struct vmstorage_channel_properties),
			 storvsc_on_channel_callback, device->channel);

	if (ret != 0)
		return ret;

	ret = storvsc_channel_init(device);

	return ret;
}