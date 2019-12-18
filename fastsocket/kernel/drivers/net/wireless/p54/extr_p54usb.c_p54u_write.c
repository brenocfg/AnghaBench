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
struct net2280_reg_write {void* val; void* addr; int /*<<< orphan*/  port; } ;
typedef  enum net2280_op_type { ____Placeholder_net2280_op_type } net2280_op_type ;
typedef  void* __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  P54U_PIPE_BRG ; 
 int /*<<< orphan*/  P54U_PIPE_DEV ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,unsigned int,struct net2280_reg_write*,int,int*,int) ; 
 unsigned int usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p54u_write(struct p54u_priv *priv,
		      struct net2280_reg_write *buf,
		      enum net2280_op_type type,
		      __le32 addr, __le32 val)
{
	unsigned int ep;
	int alen;

	if (type & 0x0800)
		ep = usb_sndbulkpipe(priv->udev, P54U_PIPE_DEV);
	else
		ep = usb_sndbulkpipe(priv->udev, P54U_PIPE_BRG);

	buf->port = cpu_to_le16(type);
	buf->addr = addr;
	buf->val = val;

	return usb_bulk_msg(priv->udev, ep, buf, sizeof(*buf), &alen, 1000);
}