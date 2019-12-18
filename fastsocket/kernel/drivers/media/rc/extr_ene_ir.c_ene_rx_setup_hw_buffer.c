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
typedef  int u16 ;
struct ene_device {int r_pointer; int w_pointer; int hw_extra_buffer; int buffer_len; int extra_buf1_address; int extra_buf1_len; int extra_buf2_address; int extra_buf2_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_FW1 ; 
 int /*<<< orphan*/  ENE_FW1_EXTRA_BUF_HND ; 
 int ENE_FW_PACKET_SIZE ; 
 scalar_t__ ENE_FW_SAMPLE_BUFFER ; 
 int /*<<< orphan*/  ene_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_notice (char*,...) ; 
 int ene_read_reg (struct ene_device*,scalar_t__) ; 
 int /*<<< orphan*/  ene_rx_read_hw_pointer (struct ene_device*) ; 
 int /*<<< orphan*/  ene_set_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_warn (char*) ; 

__attribute__((used)) static void ene_rx_setup_hw_buffer(struct ene_device *dev)
{
	u16 tmp;

	ene_rx_read_hw_pointer(dev);
	dev->r_pointer = dev->w_pointer;

	if (!dev->hw_extra_buffer) {
		dev->buffer_len = ENE_FW_PACKET_SIZE * 2;
		return;
	}

	tmp = ene_read_reg(dev, ENE_FW_SAMPLE_BUFFER);
	tmp |= ene_read_reg(dev, ENE_FW_SAMPLE_BUFFER+1) << 8;
	dev->extra_buf1_address = tmp;

	dev->extra_buf1_len = ene_read_reg(dev, ENE_FW_SAMPLE_BUFFER + 2);

	tmp = ene_read_reg(dev, ENE_FW_SAMPLE_BUFFER + 3);
	tmp |= ene_read_reg(dev, ENE_FW_SAMPLE_BUFFER + 4) << 8;
	dev->extra_buf2_address = tmp;

	dev->extra_buf2_len = ene_read_reg(dev, ENE_FW_SAMPLE_BUFFER + 5);

	dev->buffer_len = dev->extra_buf1_len + dev->extra_buf2_len + 8;

	ene_notice("Hardware uses 2 extended buffers:");
	ene_notice("  0x%04x - len : %d", dev->extra_buf1_address,
						dev->extra_buf1_len);
	ene_notice("  0x%04x - len : %d", dev->extra_buf2_address,
						dev->extra_buf2_len);

	ene_notice("Total buffer len = %d", dev->buffer_len);

	if (dev->buffer_len > 64 || dev->buffer_len < 16)
		goto error;

	if (dev->extra_buf1_address > 0xFBFC ||
					dev->extra_buf1_address < 0xEC00)
		goto error;

	if (dev->extra_buf2_address > 0xFBFC ||
					dev->extra_buf2_address < 0xEC00)
		goto error;

	if (dev->r_pointer > dev->buffer_len)
		goto error;

	ene_set_reg_mask(dev, ENE_FW1, ENE_FW1_EXTRA_BUF_HND);
	return;
error:
	ene_warn("Error validating extra buffers, device probably won't work");
	dev->hw_extra_buffer = false;
	ene_clear_reg_mask(dev, ENE_FW1, ENE_FW1_EXTRA_BUF_HND);
}