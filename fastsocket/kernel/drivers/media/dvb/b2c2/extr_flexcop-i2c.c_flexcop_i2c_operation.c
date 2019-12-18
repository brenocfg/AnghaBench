#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct flexcop_device {TYPE_2__ (* read_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ;} ;
struct TYPE_8__ {int working_start; scalar_t__ st_done; int /*<<< orphan*/  no_base_addr_ack_error; } ;
struct TYPE_9__ {int raw; TYPE_1__ tw_sm_c_100; } ;
typedef  TYPE_2__ flexcop_ibi_value ;

/* Variables and functions */
 int EREMOTEIO ; 
 int FC_MAX_I2C_RETRIES ; 
 int /*<<< orphan*/  deb_i2c (char*,...) ; 
 TYPE_2__ ibi_zero ; 
 int /*<<< orphan*/  stub1 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  stub2 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ; 
 TYPE_2__ stub3 (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_sm_c_100 ; 

__attribute__((used)) static int flexcop_i2c_operation(struct flexcop_device *fc,
		flexcop_ibi_value *r100)
{
	int i;
	flexcop_ibi_value r;

	r100->tw_sm_c_100.working_start = 1;
	deb_i2c("r100 before: %08x\n",r100->raw);

	fc->write_ibi_reg(fc, tw_sm_c_100, ibi_zero);
	fc->write_ibi_reg(fc, tw_sm_c_100, *r100); /* initiating i2c operation */

	for (i = 0; i < FC_MAX_I2C_RETRIES; i++) {
		r = fc->read_ibi_reg(fc, tw_sm_c_100);

		if (!r.tw_sm_c_100.no_base_addr_ack_error) {
			if (r.tw_sm_c_100.st_done) {
				*r100 = r;
				deb_i2c("i2c success\n");
				return 0;
			}
		} else {
			deb_i2c("suffering from an i2c ack_error\n");
			return -EREMOTEIO;
		}
	}
	deb_i2c("tried %d times i2c operation, "
			"never finished or too many ack errors.\n", i);
	return -EREMOTEIO;
}