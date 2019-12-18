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
struct i2c_msg {int len; unsigned char* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDC_ADDR ; 
 int /*<<< orphan*/  DDC_SEGMENT_ADDR ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int EDID_LENGTH ; 
 int ENXIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,unsigned char) ; 

__attribute__((used)) static int
drm_do_probe_ddc_edid(struct i2c_adapter *adapter, unsigned char *buf,
		      int block, int len)
{
	unsigned char start = block * EDID_LENGTH;
	unsigned char segment = block >> 1;
	unsigned char xfers = segment ? 3 : 2;
	int ret, retries = 5;

	/* The core i2c driver will automatically retry the transfer if the
	 * adapter reports EAGAIN. However, we find that bit-banging transfers
	 * are susceptible to errors under a heavily loaded machine and
	 * generate spurious NAKs and timeouts. Retrying the transfer
	 * of the individual block a few times seems to overcome this.
	 */
	do {
		struct i2c_msg msgs[] = {
			{
				.addr	= DDC_SEGMENT_ADDR,
				.flags	= 0,
				.len	= 1,
				.buf	= &segment,
			}, {
				.addr	= DDC_ADDR,
				.flags	= 0,
				.len	= 1,
				.buf	= &start,
			}, {
				.addr	= DDC_ADDR,
				.flags	= I2C_M_RD,
				.len	= len,
				.buf	= buf,
			}
		};

	/*
	 * Avoid sending the segment addr to not upset non-compliant ddc
	 * monitors.
	 */
		ret = i2c_transfer(adapter, &msgs[3 - xfers], xfers);

		if (ret == -ENXIO) {
			DRM_DEBUG_KMS("drm: skipping non-existent adapter %s\n",
					adapter->name);
			break;
		}
	} while (ret != xfers && --retries);

	return ret == xfers ? 0 : -1;
}