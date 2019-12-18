#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  modulation; } ;
struct TYPE_6__ {TYPE_2__ vsb; } ;
struct dvb_frontend_parameters {TYPE_3__ u; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct cx23885_tsport {struct cx23885_dev* dev; } ;
struct cx23885_dev {int board; } ;
struct TYPE_4__ {struct cx23885_tsport* priv; } ;

/* Variables and functions */
#define  CX23885_BOARD_HAUPPAUGE_HVR1275 133 
#define  CX23885_BOARD_MAGICPRO_PROHDTVE2 132 
#define  CX23885_BOARD_MYGICA_X8506 131 
 int /*<<< orphan*/  GPIO_0 ; 
 int /*<<< orphan*/  GPIO_5 ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int /*<<< orphan*/  cx23885_gpio_clear (struct cx23885_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23885_gpio_set (struct cx23885_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx23885_dvb_set_frontend(struct dvb_frontend *fe,
				    struct dvb_frontend_parameters *param)
{
	struct cx23885_tsport *port = fe->dvb->priv;
	struct cx23885_dev *dev = port->dev;

	switch (dev->board) {
	case CX23885_BOARD_HAUPPAUGE_HVR1275:
		switch (param->u.vsb.modulation) {
		case VSB_8:
			cx23885_gpio_clear(dev, GPIO_5);
			break;
		case QAM_64:
		case QAM_256:
		default:
			cx23885_gpio_set(dev, GPIO_5);
			break;
		}
		break;
	case CX23885_BOARD_MYGICA_X8506:
	case CX23885_BOARD_MAGICPRO_PROHDTVE2:
		/* Select Digital TV */
		cx23885_gpio_set(dev, GPIO_0);
		break;
	}
	return 0;
}