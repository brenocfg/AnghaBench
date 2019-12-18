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
typedef  int uint8_t ;
struct max1111_data {int* tx_buf; int* rx_buf; int /*<<< orphan*/  msg; int /*<<< orphan*/  spi; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX1111_CTRL_PD0 ; 
 int MAX1111_CTRL_PD1 ; 
 int MAX1111_CTRL_SEL_SH ; 
 int MAX1111_CTRL_SGL ; 
 int MAX1111_CTRL_STR ; 
 int MAX1111_CTRL_UNI ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct max1111_data* dev_get_drvdata (struct device*) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max1111_read(struct device *dev, int channel)
{
	struct max1111_data *data = dev_get_drvdata(dev);
	uint8_t v1, v2;
	int err;

	data->tx_buf[0] = (channel << MAX1111_CTRL_SEL_SH) |
		MAX1111_CTRL_PD0 | MAX1111_CTRL_PD1 |
		MAX1111_CTRL_SGL | MAX1111_CTRL_UNI | MAX1111_CTRL_STR;

	err = spi_sync(data->spi, &data->msg);
	if (err < 0) {
		dev_err(dev, "spi_sync failed with %d\n", err);
		return err;
	}

	v1 = data->rx_buf[0];
	v2 = data->rx_buf[1];

	if ((v1 & 0xc0) || (v2 & 0x3f))
		return -EINVAL;

	return (v1 << 2) | (v2 >> 6);
}