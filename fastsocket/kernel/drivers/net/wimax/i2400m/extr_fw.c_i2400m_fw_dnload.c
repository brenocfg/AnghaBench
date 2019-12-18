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
struct i2400m_bcf_hdr {int dummy; } ;
struct i2400m {int bus_bm_retries; int boot_mode; int /*<<< orphan*/  fw_name; } ;
struct device {int dummy; } ;
typedef  enum i2400m_bri { ____Placeholder_i2400m_bri } i2400m_bri ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int I2400M_BRI_MAC_REINIT ; 
 int I2400M_BRI_SOFT ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,struct i2400m_bcf_hdr const*,size_t,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct i2400m_bcf_hdr const*,size_t) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int i2400m_bootrom_init (struct i2400m*,int) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int i2400m_dnload_bcf (struct i2400m*,struct i2400m_bcf_hdr const*,size_t) ; 
 int i2400m_dnload_finalize (struct i2400m*,struct i2400m_bcf_hdr const*,int) ; 
 int i2400m_dnload_init (struct i2400m*,struct i2400m_bcf_hdr const*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static
int i2400m_fw_dnload(struct i2400m *i2400m, const struct i2400m_bcf_hdr *bcf,
		     size_t bcf_size, enum i2400m_bri flags)
{
	int ret = 0;
	struct device *dev = i2400m_dev(i2400m);
	int count = i2400m->bus_bm_retries;

	d_fnstart(5, dev, "(i2400m %p bcf %p size %zu)\n",
		  i2400m, bcf, bcf_size);
	i2400m->boot_mode = 1;
	wmb();		/* Make sure other readers see it */
hw_reboot:
	if (count-- == 0) {
		ret = -ERESTARTSYS;
		dev_err(dev, "device rebooted too many times, aborting\n");
		goto error_too_many_reboots;
	}
	if (flags & I2400M_BRI_MAC_REINIT) {
		ret = i2400m_bootrom_init(i2400m, flags);
		if (ret < 0) {
			dev_err(dev, "bootrom init failed: %d\n", ret);
			goto error_bootrom_init;
		}
	}
	flags |= I2400M_BRI_MAC_REINIT;

	/*
	 * Initialize the download, push the bytes to the device and
	 * then jump to the new firmware. Note @ret is passed with the
	 * offset of the jump instruction to _dnload_finalize()
	 */
	ret = i2400m_dnload_init(i2400m, bcf);	/* Init device's dnload */
	if (ret == -ERESTARTSYS)
		goto error_dev_rebooted;
	if (ret < 0)
		goto error_dnload_init;

	ret = i2400m_dnload_bcf(i2400m, bcf, bcf_size);
	if (ret == -ERESTARTSYS)
		goto error_dev_rebooted;
	if (ret < 0) {
		dev_err(dev, "fw %s: download failed: %d\n",
			i2400m->fw_name, ret);
		goto error_dnload_bcf;
	}

	ret = i2400m_dnload_finalize(i2400m, bcf, ret);
	if (ret == -ERESTARTSYS)
		goto error_dev_rebooted;
	if (ret < 0) {
		dev_err(dev, "fw %s: "
			"download finalization failed: %d\n",
			i2400m->fw_name, ret);
		goto error_dnload_finalize;
	}

	d_printf(2, dev, "fw %s successfully uploaded\n",
		 i2400m->fw_name);
	i2400m->boot_mode = 0;
	wmb();		/* Make sure i2400m_msg_to_dev() sees boot_mode */
error_dnload_finalize:
error_dnload_bcf:
error_dnload_init:
error_bootrom_init:
error_too_many_reboots:
	d_fnend(5, dev, "(i2400m %p bcf %p size %zu) = %d\n",
		i2400m, bcf, bcf_size, ret);
	return ret;

error_dev_rebooted:
	dev_err(dev, "device rebooted, %d tries left\n", count);
	/* we got the notification already, no need to wait for it again */
	flags |= I2400M_BRI_SOFT;
	goto hw_reboot;
}