#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int stype; } ;
struct vio_net_attr_info {TYPE_1__ tag; } ;
struct vio_driver_state {int dummy; } ;

/* Variables and functions */
 int ECONNRESET ; 
#define  VIO_SUBTYPE_ACK 130 
#define  VIO_SUBTYPE_INFO 129 
#define  VIO_SUBTYPE_NACK 128 
 int handle_attr_ack (struct vio_driver_state*,struct vio_net_attr_info*) ; 
 int handle_attr_info (struct vio_driver_state*,struct vio_net_attr_info*) ; 
 int handle_attr_nack (struct vio_driver_state*,struct vio_net_attr_info*) ; 

__attribute__((used)) static int vnet_handle_attr(struct vio_driver_state *vio, void *arg)
{
	struct vio_net_attr_info *pkt = arg;

	switch (pkt->tag.stype) {
	case VIO_SUBTYPE_INFO:
		return handle_attr_info(vio, pkt);

	case VIO_SUBTYPE_ACK:
		return handle_attr_ack(vio, pkt);

	case VIO_SUBTYPE_NACK:
		return handle_attr_nack(vio, pkt);

	default:
		return -ECONNRESET;
	}
}