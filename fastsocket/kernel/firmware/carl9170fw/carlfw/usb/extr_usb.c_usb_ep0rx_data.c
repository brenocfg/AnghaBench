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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GET_ARRAY (void const*,unsigned int) ; 
 int /*<<< orphan*/  get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (unsigned int const,unsigned int) ; 

__attribute__((used)) static void usb_ep0rx_data(const void *data, const unsigned int len)
{
	unsigned int offset;
	uint32_t value;

	BUG_ON(len > AR9170_USB_EP_CTRL_MAX);
	BUILD_BUG_ON(len > AR9170_USB_EP_CTRL_MAX);

	for (offset = 0; offset < ((len + 3) & ~3); offset += 4) {
		value = get(AR9170_USB_REG_EP0_DATA);
		memcpy(GET_ARRAY(data, offset), &value,
		       min(len - offset, (unsigned int)4));
	}
}