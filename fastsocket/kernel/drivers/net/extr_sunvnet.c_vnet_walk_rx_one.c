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
typedef  int /*<<< orphan*/  u32 ;
struct vio_driver_state {int dummy; } ;
struct vnet_port {struct vio_driver_state vio; } ;
struct TYPE_3__ {scalar_t__ state; int ack; } ;
struct vio_net_desc {TYPE_1__ hdr; int /*<<< orphan*/  ncookies; TYPE_2__* cookies; int /*<<< orphan*/  size; } ;
struct vio_dring_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cookie_size; int /*<<< orphan*/  cookie_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int ECONNRESET ; 
 scalar_t__ IS_ERR (struct vio_net_desc*) ; 
 int PTR_ERR (struct vio_net_desc*) ; 
 scalar_t__ VIO_DESC_DONE ; 
 scalar_t__ VIO_DESC_READY ; 
 struct vio_net_desc* get_rx_desc (struct vnet_port*,struct vio_dring_state*,int /*<<< orphan*/ ) ; 
 int put_rx_desc (struct vnet_port*,struct vio_dring_state*,struct vio_net_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vnet_rx_one (struct vnet_port*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vnet_walk_rx_one(struct vnet_port *port,
			    struct vio_dring_state *dr,
			    u32 index, int *needs_ack)
{
	struct vio_net_desc *desc = get_rx_desc(port, dr, index);
	struct vio_driver_state *vio = &port->vio;
	int err;

	if (IS_ERR(desc))
		return PTR_ERR(desc);

	viodbg(DATA, "vio_walk_rx_one desc[%02x:%02x:%08x:%08x:%llx:%llx]\n",
	       desc->hdr.state, desc->hdr.ack,
	       desc->size, desc->ncookies,
	       desc->cookies[0].cookie_addr,
	       desc->cookies[0].cookie_size);

	if (desc->hdr.state != VIO_DESC_READY)
		return 1;
	err = vnet_rx_one(port, desc->size, desc->cookies, desc->ncookies);
	if (err == -ECONNRESET)
		return err;
	desc->hdr.state = VIO_DESC_DONE;
	err = put_rx_desc(port, dr, desc, index);
	if (err < 0)
		return err;
	*needs_ack = desc->hdr.ack;
	return 0;
}