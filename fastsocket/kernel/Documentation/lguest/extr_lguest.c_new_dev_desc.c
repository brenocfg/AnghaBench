#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct lguest_device_desc {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  d ;
struct TYPE_6__ {TYPE_1__* desc; } ;
struct TYPE_5__ {void* descpage; TYPE_3__* lastdev; } ;
struct TYPE_4__ {int config_len; } ;

/* Variables and functions */
 void* device_config (TYPE_3__*) ; 
 TYPE_2__ devices ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int getpagesize () ; 
 struct lguest_device_desc* memcpy (void*,struct lguest_device_desc*,int) ; 

__attribute__((used)) static struct lguest_device_desc *new_dev_desc(u16 type)
{
	struct lguest_device_desc d = { .type = type };
	void *p;

	/* Figure out where the next device config is, based on the last one. */
	if (devices.lastdev)
		p = device_config(devices.lastdev)
			+ devices.lastdev->desc->config_len;
	else
		p = devices.descpage;

	/* We only have one page for all the descriptors. */
	if (p + sizeof(d) > (void *)devices.descpage + getpagesize())
		errx(1, "Too many devices");

	/* p might not be aligned, so we memcpy in. */
	return memcpy(p, &d, sizeof(d));
}