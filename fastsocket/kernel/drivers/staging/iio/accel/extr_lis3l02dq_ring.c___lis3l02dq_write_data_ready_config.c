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
struct iio_event_handler_list {int dummy; } ;
struct iio_dev {TYPE_1__** interrupts; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIS3L02DQ_REG_CTRL_2_ADDR ; 
 int LIS3L02DQ_REG_CTRL_2_ENABLE_DATA_READY_GENERATION ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iio_add_event_to_list (struct iio_event_handler_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_remove_event_from_list (struct iio_event_handler_list*,int /*<<< orphan*/ *) ; 
 int lis3l02dq_spi_read_reg_8 (struct device*,int /*<<< orphan*/ ,int*) ; 
 int lis3l02dq_spi_write_reg_8 (struct device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int __lis3l02dq_write_data_ready_config(struct device *dev,
					       struct
					       iio_event_handler_list *list,
					       bool state)
{
	int ret;
	u8 valold;
	bool currentlyset;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);

/* Get the current event mask register */
	ret = lis3l02dq_spi_read_reg_8(dev,
				       LIS3L02DQ_REG_CTRL_2_ADDR,
				       &valold);
	if (ret)
		goto error_ret;
/* Find out if data ready is already on */
	currentlyset
		= valold & LIS3L02DQ_REG_CTRL_2_ENABLE_DATA_READY_GENERATION;

/* Disable requested */
	if (!state && currentlyset) {

		valold &= ~LIS3L02DQ_REG_CTRL_2_ENABLE_DATA_READY_GENERATION;
		/* The double write is to overcome a hardware bug?*/
		ret = lis3l02dq_spi_write_reg_8(dev,
						LIS3L02DQ_REG_CTRL_2_ADDR,
						&valold);
		if (ret)
			goto error_ret;
		ret = lis3l02dq_spi_write_reg_8(dev,
						LIS3L02DQ_REG_CTRL_2_ADDR,
						&valold);
		if (ret)
			goto error_ret;

		iio_remove_event_from_list(list,
					   &indio_dev->interrupts[0]
					   ->ev_list);

/* Enable requested */
	} else if (state && !currentlyset) {
		/* if not set, enable requested */
		valold |= LIS3L02DQ_REG_CTRL_2_ENABLE_DATA_READY_GENERATION;
		iio_add_event_to_list(list, &indio_dev->interrupts[0]->ev_list);
		ret = lis3l02dq_spi_write_reg_8(dev,
						LIS3L02DQ_REG_CTRL_2_ADDR,
						&valold);
		if (ret)
			goto error_ret;
	}

	return 0;
error_ret:
	return ret;
}