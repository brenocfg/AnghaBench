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
typedef  int u8 ;
struct s921_isdb_t {int (* i2c_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  priv_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int s921_isdb_get_status(struct s921_isdb_t *dev, void *data) {
	unsigned int *ret = (unsigned int*)data;
	u8 ifagc_dt;
	u8 rfagc_dt;

	mdelay(10);
	ifagc_dt = dev->i2c_read(dev->priv_dev, 0x81);
	rfagc_dt = dev->i2c_read(dev->priv_dev, 0x82);
	if (rfagc_dt == 0x40) {
		*ret = 1;
	}
	return 0;
}