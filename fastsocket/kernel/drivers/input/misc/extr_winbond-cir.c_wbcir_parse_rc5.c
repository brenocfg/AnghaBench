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
typedef  int u32 ;
struct wbcir_data {scalar_t__ irdata_error; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  get_bits (struct wbcir_data*,int) ; 
 int wbcir_get_rc5bits (struct wbcir_data*,int) ; 
 int /*<<< orphan*/  wbcir_keydown (struct wbcir_data*,int,int) ; 

__attribute__((used)) static void
wbcir_parse_rc5(struct device *dev, struct wbcir_data *data)
{
	/*
	 * Bits are manchester coded as follows:
	 * cell1 + cell0 = logic "0"
	 * cell0 + cell1 = logic "1"
	 * (i.e. the reverse of RC6)
	 *
	 * Start bit 1		- "1" - discarded
	 * Start bit 2		- Must be inverted to get command bit 6
	 * Toggle bit
	 * Address Bit 4 - 0
	 * Command Bit 5 - 0
	 */
	u8 toggle;
	u8 address;
	u8 command;
	u32 scancode;

	/* Start bit 1 */
	if (!get_bits(data, 1)) {
		dev_dbg(dev, "RC5 - Invalid start bit\n");
		return;
	}

	/* Start bit 2 */
	if (!wbcir_get_rc5bits(data, 1))
		command = 0x40;
	else
		command = 0x00;

	toggle   = wbcir_get_rc5bits(data, 1);
	address  = wbcir_get_rc5bits(data, 5);
	command |= wbcir_get_rc5bits(data, 6);
	scancode = address << 7 | command;

	/* Last sanity check */
	if (data->irdata_error) {
		dev_dbg(dev, "RC5 - Invalid message\n");
		return;
	}

	dev_dbg(dev, "IR-RC5 ad %u cm %u t %u s %u\n",
		(unsigned int)address,
		(unsigned int)command,
		(unsigned int)toggle,
		(unsigned int)scancode);

	wbcir_keydown(data, scancode, toggle);
}