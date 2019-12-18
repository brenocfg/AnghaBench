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
typedef  int u32 ;
struct cx25821_dev {int _max_num_decoders; int /*<<< orphan*/  lock; int /*<<< orphan*/ * i2c_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_AB_DIAG_CTRL ; 
 int /*<<< orphan*/  BYP_AB_CTRL ; 
 int /*<<< orphan*/  DENC_AB_CTRL ; 
 int EINVAL ; 
 int MAX_DECODERS ; 
 int /*<<< orphan*/  MON_A_CTRL ; 
 int /*<<< orphan*/  PIN_OE_CTRL ; 
 int /*<<< orphan*/ * _display_field_cnt ; 
 int _num_decoders ; 
 int cx25821_i2c_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int cx25821_i2c_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  medusa_set_decoderduration (struct cx25821_dev*,int,int /*<<< orphan*/ ) ; 
 int medusa_set_videostandard (struct cx25821_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int medusa_video_init(struct cx25821_dev *dev)
{
	u32 value = 0, tmp = 0;
	int ret_val = 0;
	int i = 0;

	mutex_lock(&dev->lock);

	_num_decoders = dev->_max_num_decoders;

	// disable Auto source selection on all video decoders
	value = cx25821_i2c_read(&dev->i2c_bus[0], MON_A_CTRL, &tmp);
	value &= 0xFFFFF0FF;
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], MON_A_CTRL, value);

	if (ret_val < 0) {
		mutex_unlock(&dev->lock);
		return -EINVAL;
	}
	// Turn off Master source switch enable
	value = cx25821_i2c_read(&dev->i2c_bus[0], MON_A_CTRL, &tmp);
	value &= 0xFFFFFFDF;
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], MON_A_CTRL, value);

	if (ret_val < 0) {
		mutex_unlock(&dev->lock);
		return -EINVAL;
	}

	mutex_unlock(&dev->lock);

	for (i = 0; i < _num_decoders; i++) {
		medusa_set_decoderduration(dev, i, _display_field_cnt[i]);
	}

	mutex_lock(&dev->lock);

	// Select monitor as DENC A input, power up the DAC
	value = cx25821_i2c_read(&dev->i2c_bus[0], DENC_AB_CTRL, &tmp);
	value &= 0xFF70FF70;
	value |= 0x00090008;	// set en_active
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], DENC_AB_CTRL, value);

	if (ret_val < 0) {
		mutex_unlock(&dev->lock);
		return -EINVAL;
	}
	// enable input is VIP/656
	value = cx25821_i2c_read(&dev->i2c_bus[0], BYP_AB_CTRL, &tmp);
	value |= 0x00040100;	// enable VIP
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], BYP_AB_CTRL, value);

	if (ret_val < 0) {
		mutex_unlock(&dev->lock);
		return -EINVAL;
	}
	// select AFE clock to output mode
	value = cx25821_i2c_read(&dev->i2c_bus[0], AFE_AB_DIAG_CTRL, &tmp);
	value &= 0x83FFFFFF;
	ret_val =
	    cx25821_i2c_write(&dev->i2c_bus[0], AFE_AB_DIAG_CTRL,
			      value | 0x10000000);

	if (ret_val < 0) {
		mutex_unlock(&dev->lock);
		return -EINVAL;
	}
	// Turn on all of the data out and control output pins.
	value = cx25821_i2c_read(&dev->i2c_bus[0], PIN_OE_CTRL, &tmp);
	value &= 0xFEF0FE00;
	if (_num_decoders == MAX_DECODERS) {
		// Note: The octal board does not support control pins(bit16-19).
		// These bits are ignored in the octal board.
		value |= 0x010001F8;	// disable VDEC A-C port, default to Mobilygen Interface
	} else {
		value |= 0x010F0108;	// disable VDEC A-C port, default to Mobilygen Interface
	}

	value |= 7;
	ret_val = cx25821_i2c_write(&dev->i2c_bus[0], PIN_OE_CTRL, value);
	if (ret_val < 0) {
		mutex_unlock(&dev->lock);
		return -EINVAL;
	}

	mutex_unlock(&dev->lock);

	ret_val = medusa_set_videostandard(dev);

	if (ret_val < 0) {
		mutex_unlock(&dev->lock);
		return -EINVAL;
	}

	return 1;
}