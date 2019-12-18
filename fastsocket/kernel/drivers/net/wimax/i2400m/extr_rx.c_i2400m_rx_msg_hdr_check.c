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
struct i2400m_msg_hdr {scalar_t__ barker; scalar_t__ num_pls; } ;
struct i2400m {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2400M_D2H_MSG_BARKER ; 
 scalar_t__ I2400M_MAX_PLS_IN_MSG ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static
int i2400m_rx_msg_hdr_check(struct i2400m *i2400m,
			    const struct i2400m_msg_hdr *msg_hdr,
			    size_t buf_size)
{
	int result = -EIO;
	struct device *dev = i2400m_dev(i2400m);
	if (buf_size < sizeof(*msg_hdr)) {
		dev_err(dev, "RX: HW BUG? message with short header (%zu "
			"vs %zu bytes expected)\n", buf_size, sizeof(*msg_hdr));
		goto error;
	}
	if (msg_hdr->barker != cpu_to_le32(I2400M_D2H_MSG_BARKER)) {
		dev_err(dev, "RX: HW BUG? message received with unknown "
			"barker 0x%08x (buf_size %zu bytes)\n",
			le32_to_cpu(msg_hdr->barker), buf_size);
		goto error;
	}
	if (msg_hdr->num_pls == 0) {
		dev_err(dev, "RX: HW BUG? zero payload packets in message\n");
		goto error;
	}
	if (le16_to_cpu(msg_hdr->num_pls) > I2400M_MAX_PLS_IN_MSG) {
		dev_err(dev, "RX: HW BUG? message contains more payload "
			"than maximum; ignoring.\n");
		goto error;
	}
	result = 0;
error:
	return result;
}