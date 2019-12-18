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
struct dvb_frontend_parameters {int dummy; } ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
#define  DVB_FE_IOCTL_POST 130 
#define  DVB_FE_IOCTL_PRE 129 
#define  FE_SET_FRONTEND 128 
 int cx23885_dvb_set_frontend (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 

__attribute__((used)) static int cx23885_dvb_fe_ioctl_override(struct dvb_frontend *fe,
					 unsigned int cmd, void *parg,
					 unsigned int stage)
{
	int err = 0;

	switch (stage) {
	case DVB_FE_IOCTL_PRE:

		switch (cmd) {
		case FE_SET_FRONTEND:
			err = cx23885_dvb_set_frontend(fe,
				(struct dvb_frontend_parameters *) parg);
			break;
		}
		break;

	case DVB_FE_IOCTL_POST:
		/* no post-ioctl handling required */
		break;
	}
	return err;
}