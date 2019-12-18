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
typedef  int u16 ;
struct flexcop_device {int (* i2c_request ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int*,int) ;int /*<<< orphan*/ * fc_i2c_adap; } ;
typedef  int /*<<< orphan*/  flexcop_access_op_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int*,int) ; 

__attribute__((used)) static int flexcop_eeprom_request(struct flexcop_device *fc,
	flexcop_access_op_t op, u16 addr, u8 *buf, u16 len, int retries)
{
	int i,ret = 0;
	u8 chipaddr =  0x50 | ((addr >> 8) & 3);
	for (i = 0; i < retries; i++) {
		ret = fc->i2c_request(&fc->fc_i2c_adap[1], op, chipaddr,
			addr & 0xff, buf, len);
		if (ret == 0)
			break;
	}
	return ret;
}