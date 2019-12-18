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
struct s921_isdb_t_transmission_mode_params {int dummy; } ;
struct s921_isdb_t {int (* i2c_write ) (int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  priv_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int E_OK ; 
 int stub1 (int /*<<< orphan*/ ,int,int) ; 
 int stub2 (int /*<<< orphan*/ ,int,int) ; 
 int stub3 (int /*<<< orphan*/ ,int,int) ; 
 int stub4 (int /*<<< orphan*/ ,int,int) ; 
 int stub5 (int /*<<< orphan*/ ,int,int) ; 
 int stub6 (int /*<<< orphan*/ ,int,int) ; 
 int stub7 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int s921_isdb_set_parameters(struct s921_isdb_t *dev, struct s921_isdb_t_transmission_mode_params *params) {

	int ret;
	/* auto is sufficient for now, lateron this should be reflected in an extra interface */



	ret = dev->i2c_write(dev->priv_dev, 0xb0, 0xa0); //mod_b2);
	ret = dev->i2c_write(dev->priv_dev, 0xb2, 0x3d); //mod_b2);

	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xb3, 0x25); //mod_b3);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xb4, 0x8b); //mod_b4);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xb5, 0x4b); //mod_b5);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xb6, 0x3f); //mod_b6);
	if (ret < 0)
		return -EINVAL;

	ret = dev->i2c_write(dev->priv_dev, 0xb7, 0x3f); //mod_b7);
	if (ret < 0)
		return -EINVAL;

	return E_OK;
}