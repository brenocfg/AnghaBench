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
struct p54u_priv {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int p54u_bulk_msg(struct p54u_priv *priv, unsigned int ep,
			 void *data, size_t len)
{
	int alen;
	return usb_bulk_msg(priv->udev, usb_sndbulkpipe(priv->udev, ep),
			    data, len, &alen, 2000);
}