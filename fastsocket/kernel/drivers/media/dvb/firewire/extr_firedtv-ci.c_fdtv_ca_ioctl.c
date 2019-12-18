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
struct inode {int dummy; } ;
struct firedtv_tuner_status {int dummy; } ;
struct firedtv {int /*<<< orphan*/  device; } ;
struct file {struct dvb_device* private_data; } ;
struct dvb_device {struct firedtv* priv; } ;

/* Variables and functions */
#define  CA_GET_CAP 132 
#define  CA_GET_MSG 131 
#define  CA_GET_SLOT_INFO 130 
#define  CA_RESET 129 
#define  CA_SEND_MSG 128 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  avc_tuner_status (struct firedtv*,struct firedtv_tuner_status*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int fdtv_ca_get_caps (void*) ; 
 int fdtv_ca_get_msg (struct firedtv*,void*) ; 
 int fdtv_ca_get_slot_info (struct firedtv*,void*) ; 
 int fdtv_ca_reset (struct firedtv*) ; 
 int fdtv_ca_send_msg (struct firedtv*,void*) ; 

__attribute__((used)) static int fdtv_ca_ioctl(struct inode *inode, struct file *file,
			    unsigned int cmd, void *arg)
{
	struct dvb_device *dvbdev = file->private_data;
	struct firedtv *fdtv = dvbdev->priv;
	struct firedtv_tuner_status stat;
	int err;

	switch (cmd) {
	case CA_RESET:
		err = fdtv_ca_reset(fdtv);
		break;
	case CA_GET_CAP:
		err = fdtv_ca_get_caps(arg);
		break;
	case CA_GET_SLOT_INFO:
		err = fdtv_ca_get_slot_info(fdtv, arg);
		break;
	case CA_GET_MSG:
		err = fdtv_ca_get_msg(fdtv, arg);
		break;
	case CA_SEND_MSG:
		err = fdtv_ca_send_msg(fdtv, arg);
		break;
	default:
		dev_info(fdtv->device, "unhandled CA ioctl %u\n", cmd);
		err = -EOPNOTSUPP;
	}

	/* FIXME Is this necessary? */
	avc_tuner_status(fdtv, &stat);

	return err;
}