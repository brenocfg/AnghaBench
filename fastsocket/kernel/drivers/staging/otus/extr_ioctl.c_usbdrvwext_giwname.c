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
union iwreq_data {int /*<<< orphan*/  name; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int usbdrvwext_giwname(struct net_device *dev,
		struct iw_request_info *info,
		union iwreq_data *wrq, char *extra)
{
	/* struct usbdrv_private *macp = dev->ml_priv; */

	strcpy(wrq->name, "IEEE 802.11-MIMO");

	return 0;
}