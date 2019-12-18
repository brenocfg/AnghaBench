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
struct dvb_frontend {struct vp702x_fe_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct vp702x_fe_state {int* lnb_buf; struct dvb_frontend fe; struct dvb_usb_device* d; } ;
struct dvb_usb_device {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SET_LNB_POWER ; 
 struct vp702x_fe_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vp702x_fe_ops ; 

struct dvb_frontend * vp702x_fe_attach(struct dvb_usb_device *d)
{
	struct vp702x_fe_state *s = kzalloc(sizeof(struct vp702x_fe_state), GFP_KERNEL);
	if (s == NULL)
		goto error;

	s->d = d;

	memcpy(&s->fe.ops,&vp702x_fe_ops,sizeof(struct dvb_frontend_ops));
	s->fe.demodulator_priv = s;

	s->lnb_buf[1] = SET_LNB_POWER;
	s->lnb_buf[3] = 0xff; /* 0=tone burst, 2=data burst, ff=off */

	return &s->fe;
error:
	return NULL;
}