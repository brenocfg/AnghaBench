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
struct vio_version {scalar_t__ major; scalar_t__ minor; } ;
struct TYPE_2__ {void* stype; int /*<<< orphan*/  sid; } ;
struct vio_ver_info {scalar_t__ major; scalar_t__ minor; TYPE_1__ tag; int /*<<< orphan*/  dev_class; } ;
struct vio_driver_state {scalar_t__ hs_state; struct vio_version ver; int /*<<< orphan*/  _peer_sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 scalar_t__ VIO_HS_GOTVERS ; 
 scalar_t__ VIO_HS_INVALID ; 
 void* VIO_SUBTYPE_ACK ; 
 void* VIO_SUBTYPE_NACK ; 
 struct vio_version* find_by_major (struct vio_driver_state*,scalar_t__) ; 
 int handshake_failure (struct vio_driver_state*) ; 
 int /*<<< orphan*/  memset (struct vio_version*,int /*<<< orphan*/ ,int) ; 
 int send_ctrl (struct vio_driver_state*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int process_ver_info(struct vio_driver_state *vio,
			    struct vio_ver_info *pkt)
{
	struct vio_version *vap;
	int err;

	viodbg(HS, "GOT VERSION INFO maj[%u] min[%u] devclass[%u]\n",
	       pkt->major, pkt->minor, pkt->dev_class);

	if (vio->hs_state != VIO_HS_INVALID) {
		/* XXX Perhaps invoke start_handshake? XXX */
		memset(&vio->ver, 0, sizeof(vio->ver));
		vio->hs_state = VIO_HS_INVALID;
	}

	vap = find_by_major(vio, pkt->major);

	vio->_peer_sid = pkt->tag.sid;

	if (!vap) {
		pkt->tag.stype = VIO_SUBTYPE_NACK;
		pkt->major = 0;
		pkt->minor = 0;
		viodbg(HS, "SEND VERSION NACK maj[0] min[0]\n");
		err = send_ctrl(vio, &pkt->tag, sizeof(*pkt));
	} else if (vap->major != pkt->major) {
		pkt->tag.stype = VIO_SUBTYPE_NACK;
		pkt->major = vap->major;
		pkt->minor = vap->minor;
		viodbg(HS, "SEND VERSION NACK maj[%u] min[%u]\n",
		       pkt->major, pkt->minor);
		err = send_ctrl(vio, &pkt->tag, sizeof(*pkt));
	} else {
		struct vio_version ver = {
			.major = pkt->major,
			.minor = pkt->minor,
		};
		if (ver.minor > vap->minor)
			ver.minor = vap->minor;
		pkt->minor = ver.minor;
		pkt->tag.stype = VIO_SUBTYPE_ACK;
		viodbg(HS, "SEND VERSION ACK maj[%u] min[%u]\n",
		       pkt->major, pkt->minor);
		err = send_ctrl(vio, &pkt->tag, sizeof(*pkt));
		if (err > 0) {
			vio->ver = ver;
			vio->hs_state = VIO_HS_GOTVERS;
		}
	}
	if (err < 0)
		return handshake_failure(vio);

	return 0;
}