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
typedef  int u8 ;
struct sca3000_state {int /*<<< orphan*/  lock; TYPE_1__* info; } ;
struct iio_dev {struct sca3000_state* dev_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  option_mode_2; int /*<<< orphan*/  option_mode_1; } ;

/* Variables and functions */
#define  SCA3000_MEAS_MODE_MOT_DET 134 
#define  SCA3000_MEAS_MODE_NORMAL 133 
#define  SCA3000_MEAS_MODE_OP_1 132 
#define  SCA3000_MEAS_MODE_OP_2 131 
#define  SCA3000_OP_MODE_BYPASS 130 
#define  SCA3000_OP_MODE_NARROW 129 
#define  SCA3000_OP_MODE_WIDE 128 
 int /*<<< orphan*/  SCA3000_REG_ADDR_MODE ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_data (struct sca3000_state*,int /*<<< orphan*/ ,int**,int) ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t
sca3000_show_measurement_mode(struct device *dev,
			      struct device_attribute *attr,
			      char *buf)
{
	struct iio_dev *dev_info = dev_get_drvdata(dev);
	struct sca3000_state *st = dev_info->dev_data;
	int len = 0, ret;
	u8 *rx;

	mutex_lock(&st->lock);
	ret = sca3000_read_data(st, SCA3000_REG_ADDR_MODE, &rx, 1);
	if (ret)
		goto error_ret;
	/* mask bottom 2 bits - only ones that are relevant */
	rx[1] &= 0x03;
	switch (rx[1]) {
	case SCA3000_MEAS_MODE_NORMAL:
		len += sprintf(buf + len, "0 - normal mode\n");
		break;
	case SCA3000_MEAS_MODE_MOT_DET:
		len += sprintf(buf + len, "3 - motion detection\n");
		break;
	case SCA3000_MEAS_MODE_OP_1:
		switch (st->info->option_mode_1) {
		case SCA3000_OP_MODE_NARROW:
			len += sprintf(buf + len, "1 - narrow mode\n");
			break;
		case SCA3000_OP_MODE_BYPASS:
			len += sprintf(buf + len, "1 - bypass mode\n");
			break;
		};
		break;
	case SCA3000_MEAS_MODE_OP_2:
		switch (st->info->option_mode_2) {
		case SCA3000_OP_MODE_WIDE:
			len += sprintf(buf + len, "2 - wide mode\n");
			break;
		}
		break;
	};

error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}