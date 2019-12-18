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
struct i2c_adapter {int dummy; } ;
struct dvb_usb_adapter {int /*<<< orphan*/  fe; TYPE_3__* dev; } ;
struct dib0700_state {scalar_t__ is_dib7000pc; } ;
typedef  int s8 ;
struct TYPE_6__ {TYPE_2__* udev; struct dib0700_state* priv; struct i2c_adapter i2c_adap; } ;
struct TYPE_4__ {scalar_t__ idVendor; scalar_t__ idProduct; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIBX000_I2C_INTERFACE_TUNER ; 
 int ENODEV ; 
 int /*<<< orphan*/  USB_PID_HAUPPAUGE_NOVA_T_STICK ; 
 int /*<<< orphan*/  USB_VID_HAUPPAUGE ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct i2c_adapter* dib7000m_get_i2c_master (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct i2c_adapter* dib7000p_get_i2c_master (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i2c_adapter*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eeprom_read (struct i2c_adapter*,int,int*) ; 
 int /*<<< orphan*/  mt2060_attach ; 
 int /*<<< orphan*/  stk7700p_mt2060_config ; 

__attribute__((used)) static int stk7700p_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct i2c_adapter *prim_i2c = &adap->dev->i2c_adap;
	struct dib0700_state *st = adap->dev->priv;
	struct i2c_adapter *tun_i2c;
	s8 a;
	int if1=1220;
	if (adap->dev->udev->descriptor.idVendor  == cpu_to_le16(USB_VID_HAUPPAUGE) &&
		adap->dev->udev->descriptor.idProduct == cpu_to_le16(USB_PID_HAUPPAUGE_NOVA_T_STICK)) {
		if (!eeprom_read(prim_i2c,0x58,&a)) if1=1220+a;
	}
	if (st->is_dib7000pc)
		tun_i2c = dib7000p_get_i2c_master(adap->fe, DIBX000_I2C_INTERFACE_TUNER, 1);
	else
		tun_i2c = dib7000m_get_i2c_master(adap->fe, DIBX000_I2C_INTERFACE_TUNER, 1);

	return dvb_attach(mt2060_attach, adap->fe, tun_i2c, &stk7700p_mt2060_config,
		if1) == NULL ? -ENODEV : 0;
}