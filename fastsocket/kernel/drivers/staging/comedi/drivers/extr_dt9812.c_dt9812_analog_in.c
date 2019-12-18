#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct slot_dt9812 {int /*<<< orphan*/  mutex; TYPE_1__* usb; } ;
struct dt9812_rmw_byte {int address; int and_mask; int or_value; } ;
typedef  enum dt9812_gain { ____Placeholder_dt9812_gain } dt9812_gain ;
struct TYPE_5__ {int device; } ;

/* Variables and functions */
#define  DT9812_DEVID_DT9812_10 129 
#define  DT9812_DEVID_DT9812_2PT5 128 
 int ENODEV ; 
 int F020_MASK_ADC0CN_AD0BUSY ; 
 int F020_MASK_ADC0CN_AD0EN ; 
 int F020_MASK_ADC0CN_AD0INT ; 
 int F020_SFR_ADC0CN ; 
 int F020_SFR_ADC0H ; 
 int F020_SFR_ADC0L ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt9812_configure_gain (TYPE_1__*,struct dt9812_rmw_byte*,int) ; 
 int /*<<< orphan*/  dt9812_configure_mux (TYPE_1__*,struct dt9812_rmw_byte*,int) ; 
 int dt9812_read_multiple_registers (TYPE_1__*,int,int*,int*) ; 
 int dt9812_rmw_multiple_registers (TYPE_1__*,int,struct dt9812_rmw_byte*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dt9812_analog_in(struct slot_dt9812 *slot, int channel, u16 * value,
			    enum dt9812_gain gain)
{
	struct dt9812_rmw_byte rmw[3];
	u8 reg[3] = {
		F020_SFR_ADC0CN,
		F020_SFR_ADC0H,
		F020_SFR_ADC0L
	};
	u8 val[3];
	int result = -ENODEV;

	down(&slot->mutex);
	if (!slot->usb)
		goto exit;

	/* 1 select the gain */
	dt9812_configure_gain(slot->usb, &rmw[0], gain);

	/* 2 set the MUX to select the channel */
	dt9812_configure_mux(slot->usb, &rmw[1], channel);

	/* 3 start conversion */
	rmw[2].address = F020_SFR_ADC0CN;
	rmw[2].and_mask = 0xff;
	rmw[2].or_value = F020_MASK_ADC0CN_AD0EN | F020_MASK_ADC0CN_AD0BUSY;

	result = dt9812_rmw_multiple_registers(slot->usb, 3, rmw);
	if (result)
		goto exit;

	/* read the status and ADC */
	result = dt9812_read_multiple_registers(slot->usb, 3, reg, val);
	if (result)
		goto exit;
	/*
	 * An ADC conversion takes 16 SAR clocks cycles, i.e. about 9us.
	 * Therefore, between the instant that AD0BUSY was set via
	 * dt9812_rmw_multiple_registers and the read of AD0BUSY via
	 * dt9812_read_multiple_registers, the conversion should be complete
	 * since these two operations require two USB transactions each taking
	 * at least a millisecond to complete.  However, lets make sure that
	 * conversion is finished.
	 */
	if ((val[0] & (F020_MASK_ADC0CN_AD0INT | F020_MASK_ADC0CN_AD0BUSY)) ==
	    F020_MASK_ADC0CN_AD0INT) {
		switch (slot->usb->device) {
		case DT9812_DEVID_DT9812_10:
			/*
			 * For DT9812-10V the personality module set the
			 * encoding to 2's complement. Hence, convert it before
			 * returning it
			 */
			*value = ((val[1] << 8) | val[2]) + 0x800;
			break;
		case DT9812_DEVID_DT9812_2PT5:
			*value = (val[1] << 8) | val[2];
			break;
		}
	}

exit:
	up(&slot->mutex);
	return result;
}