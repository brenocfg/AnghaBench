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
typedef  int u8 ;
struct vio_msg_tag {int stype_env; } ;
struct vio_driver_state {int hs_state; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* handshake_complete ) (struct vio_driver_state*) ;} ;

/* Variables and functions */
#define  VIO_ATTR_INFO 132 
#define  VIO_DRING_REG 131 
#define  VIO_DRING_UNREG 130 
 int VIO_HS_COMPLETE ; 
#define  VIO_RDX 129 
#define  VIO_VER_INFO 128 
 int process_attr (struct vio_driver_state*,void*) ; 
 int process_dreg (struct vio_driver_state*,void*) ; 
 int process_dunreg (struct vio_driver_state*,void*) ; 
 int process_rdx (struct vio_driver_state*,void*) ; 
 int process_unknown (struct vio_driver_state*,void*) ; 
 int process_ver (struct vio_driver_state*,void*) ; 
 int /*<<< orphan*/  stub1 (struct vio_driver_state*) ; 

int vio_control_pkt_engine(struct vio_driver_state *vio, void *pkt)
{
	struct vio_msg_tag *tag = pkt;
	u8 prev_state = vio->hs_state;
	int err;

	switch (tag->stype_env) {
	case VIO_VER_INFO:
		err = process_ver(vio, pkt);
		break;

	case VIO_ATTR_INFO:
		err = process_attr(vio, pkt);
		break;

	case VIO_DRING_REG:
		err = process_dreg(vio, pkt);
		break;

	case VIO_DRING_UNREG:
		err = process_dunreg(vio, pkt);
		break;

	case VIO_RDX:
		err = process_rdx(vio, pkt);
		break;

	default:
		err = process_unknown(vio, pkt);
		break;
	}
	if (!err &&
	    vio->hs_state != prev_state &&
	    (vio->hs_state & VIO_HS_COMPLETE))
		vio->ops->handshake_complete(vio);

	return err;
}