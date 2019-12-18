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
struct dvb_frontend {TYPE_1__* dvb; } ;
struct cx88_core {int (* prev_set_voltage ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;} ;
struct cx8802_dev {struct cx88_core* core; } ;
typedef  int /*<<< orphan*/  fe_sec_voltage_t ;
struct TYPE_2__ {struct cx8802_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_GP0_IO ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int stub1 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vp1027_set_voltage(struct dvb_frontend *fe,
				    fe_sec_voltage_t voltage)
{
	struct cx8802_dev *dev = fe->dvb->priv;
	struct cx88_core *core = dev->core;

	switch (voltage) {
	case SEC_VOLTAGE_13:
		dprintk(1, "LNB SEC Voltage=13\n");
		cx_write(MO_GP0_IO, 0x00001220);
		break;
	case SEC_VOLTAGE_18:
		dprintk(1, "LNB SEC Voltage=18\n");
		cx_write(MO_GP0_IO, 0x00001222);
		break;
	case SEC_VOLTAGE_OFF:
		dprintk(1, "LNB Voltage OFF\n");
		cx_write(MO_GP0_IO, 0x00001230);
		break;
	}

	if (core->prev_set_voltage)
		return core->prev_set_voltage(fe, voltage);
	return 0;
}