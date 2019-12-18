#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {TYPE_2__* udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  devpath; TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTL_OTHER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTL_THIS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_link (struct usbnet*) ; 

__attribute__((used)) static inline void nc_dump_ttl(struct usbnet *dev, u16 ttl)
{
	if (netif_msg_link(dev))
		devdbg(dev, "net1080 %s-%s ttl 0x%x this = %d, other = %d",
			dev->udev->bus->bus_name, dev->udev->devpath,
			ttl, TTL_THIS(ttl), TTL_OTHER(ttl));
}