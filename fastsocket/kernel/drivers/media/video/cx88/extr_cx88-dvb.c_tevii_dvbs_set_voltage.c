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
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int stub1 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tevii_dvbs_set_voltage(struct dvb_frontend *fe,
				      fe_sec_voltage_t voltage)
{
	struct cx8802_dev *dev= fe->dvb->priv;
	struct cx88_core *core = dev->core;

	cx_set(MO_GP0_IO, 0x6040);
	switch (voltage) {
	case SEC_VOLTAGE_13:
		cx_clear(MO_GP0_IO, 0x20);
		break;
	case SEC_VOLTAGE_18:
		cx_set(MO_GP0_IO, 0x20);
		break;
	case SEC_VOLTAGE_OFF:
		cx_clear(MO_GP0_IO, 0x20);
		break;
	}

	if (core->prev_set_voltage)
		return core->prev_set_voltage(fe, voltage);
	return 0;
}