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
struct usbnet {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devinfo (struct usbnet*,char*,int,int) ; 
 scalar_t__ netif_msg_timer (struct usbnet*) ; 

__attribute__((used)) static void dumpspeed(struct usbnet *dev, __le32 *speeds)
{
	if (netif_msg_timer(dev))
		devinfo(dev, "link speeds: %u kbps up, %u kbps down",
			__le32_to_cpu(speeds[0]) / 1000,
		__le32_to_cpu(speeds[1]) / 1000);
}