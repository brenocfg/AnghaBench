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
struct usbnet {scalar_t__ driver_priv; } ;
struct rndis_wlan_private {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct rndis_wlan_private *get_rndis_wlan_priv(struct usbnet *dev)
{
	return (struct rndis_wlan_private *)dev->driver_priv;
}