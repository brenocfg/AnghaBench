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
struct s921_isdb_t_tune_params {int frequency; } ;
struct s921_isdb_t {int (* i2c_write ) (int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  priv_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int* c_table ; 
 int stub1 (int /*<<< orphan*/ ,int,int) ; 
 int stub10 (int /*<<< orphan*/ ,int,int) ; 
 int stub11 (int /*<<< orphan*/ ,int,int) ; 
 int stub12 (int /*<<< orphan*/ ,int,int) ; 
 int stub13 (int /*<<< orphan*/ ,int,int) ; 
 int stub14 (int /*<<< orphan*/ ,int,int) ; 
 int stub15 (int /*<<< orphan*/ ,int,int) ; 
 int stub2 (int /*<<< orphan*/ ,int,int) ; 
 int stub3 (int /*<<< orphan*/ ,int,int) ; 
 int stub4 (int /*<<< orphan*/ ,int,int) ; 
 int stub5 (int /*<<< orphan*/ ,int,int) ; 
 int stub6 (int /*<<< orphan*/ ,int,int) ; 
 int stub7 (int /*<<< orphan*/ ,int,int) ; 
 int stub8 (int /*<<< orphan*/ ,int,int) ; 
 int stub9 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int s921_isdb_tune(struct s921_isdb_t *dev, struct s921_isdb_t_tune_params *params) {

	int ret;
	int index;

	index = (params->frequency - 473143000)/6000000;

	if (index > 48) {
		return -EINVAL;
	}

	dev->i2c_write(dev->priv_dev, 0x47, 0x60);

	ret = dev->i2c_write(dev->priv_dev, 0x68, 0x00);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0x69, 0x89);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xf0, 0x48);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xf1, 0x19);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xf2, c_table[index*3]);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xf3, c_table[index*3+1]);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xf4, c_table[index*3+2]);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xf5, 0xae);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xf6, 0xb7);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xf7, 0xba);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xf8, 0xd7);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0x68, 0x0a);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0x69, 0x09);
	if (ret < 0)
		return -EINVAL;

	dev->i2c_write(dev->priv_dev, 0x01, 0x40);
	return 0;
}