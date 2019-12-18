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
typedef  scalar_t__ u32 ;
struct vio_msg_tag {scalar_t__ type; scalar_t__ stype; scalar_t__ stype_env; scalar_t__ sid; } ;
struct vio_driver_state {int dev_class; scalar_t__ _peer_sid; scalar_t__ _local_sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int EINVAL ; 
#define  VDEV_DISK 131 
#define  VDEV_DISK_SERVER 130 
#define  VDEV_NETWORK 129 
#define  VDEV_NETWORK_SWITCH 128 
 scalar_t__ VIO_SUBTYPE_INFO ; 
 scalar_t__ VIO_TYPE_CTRL ; 
 scalar_t__ VIO_VER_INFO ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 

int vio_validate_sid(struct vio_driver_state *vio, struct vio_msg_tag *tp)
{
	u32 sid;

	/* Always let VERSION+INFO packets through unchecked, they
	 * define the new SID.
	 */
	if (tp->type == VIO_TYPE_CTRL &&
	    tp->stype == VIO_SUBTYPE_INFO &&
	    tp->stype_env == VIO_VER_INFO)
		return 0;

	/* Ok, now figure out which SID to use.  */
	switch (vio->dev_class) {
	case VDEV_NETWORK:
	case VDEV_NETWORK_SWITCH:
	case VDEV_DISK_SERVER:
	default:
		sid = vio->_peer_sid;
		break;

	case VDEV_DISK:
		sid = vio->_local_sid;
		break;
	}

	if (sid == tp->sid)
		return 0;
	viodbg(DATA, "BAD SID tag->sid[%08x] peer_sid[%08x] local_sid[%08x]\n",
	       tp->sid, vio->_peer_sid, vio->_local_sid);
	return -EINVAL;
}