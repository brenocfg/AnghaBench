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
struct vio_driver_state {int hs_state; } ;
struct TYPE_2__ {int stype; } ;
struct vio_dring_register {TYPE_1__ tag; } ;

/* Variables and functions */
 int VIO_HS_GOTVERS ; 
#define  VIO_SUBTYPE_ACK 130 
#define  VIO_SUBTYPE_INFO 129 
#define  VIO_SUBTYPE_NACK 128 
 int handshake_failure (struct vio_driver_state*) ; 
 int process_dreg_ack (struct vio_driver_state*,struct vio_dring_register*) ; 
 int process_dreg_info (struct vio_driver_state*,struct vio_dring_register*) ; 
 int process_dreg_nack (struct vio_driver_state*,struct vio_dring_register*) ; 

__attribute__((used)) static int process_dreg(struct vio_driver_state *vio,
			struct vio_dring_register *pkt)
{
	if (!(vio->hs_state & VIO_HS_GOTVERS))
		return handshake_failure(vio);

	switch (pkt->tag.stype) {
	case VIO_SUBTYPE_INFO:
		return process_dreg_info(vio, pkt);

	case VIO_SUBTYPE_ACK:
		return process_dreg_ack(vio, pkt);

	case VIO_SUBTYPE_NACK:
		return process_dreg_nack(vio, pkt);

	default:
		return handshake_failure(vio);
	}
}