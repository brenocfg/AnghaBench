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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 unsigned int const AR9170_USB_EP_CTRL_MAX ; 
 int /*<<< orphan*/  AR9170_USB_REG_EP0_DATA ; 
 int /*<<< orphan*/  AR9170_USB_REG_FIFO_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GET_ARRAY (void const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int min (unsigned int const,unsigned int) ; 
 int /*<<< orphan*/  set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usb_ep0tx_data(const void *data, const unsigned int len)
{
	unsigned int offset = 0, block, last_block = 0;
	uint32_t value;

	BUG_ON(len > AR9170_USB_EP_CTRL_MAX);
	BUILD_BUG_ON(len > AR9170_USB_EP_CTRL_MAX);

	block = min(len, (unsigned int) 4);
	offset = 0;
	while (offset < len) {

		if (last_block != block || block < 4)
			setb(AR9170_USB_REG_FIFO_SIZE, (1 << block) - 1);

		memcpy(&value, GET_ARRAY(data, offset), block);

		set(AR9170_USB_REG_EP0_DATA, value);

		offset += block;
		last_block = block = min(len - offset, (unsigned int) 4);
	}

	setb(AR9170_USB_REG_FIFO_SIZE, 0xf);

	/* this will push the data to the host */
	return 1;
}