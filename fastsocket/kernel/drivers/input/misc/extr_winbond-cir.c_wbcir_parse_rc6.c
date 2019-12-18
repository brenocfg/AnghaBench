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
typedef  int u16 ;
struct wbcir_data {scalar_t__ irdata_error; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int get_bits (struct wbcir_data*,int) ; 
 int /*<<< orphan*/  wbcir_keydown (struct wbcir_data*,int,int) ; 
 int wbcir_rc6cells_to_byte (struct wbcir_data*) ; 

__attribute__((used)) static void
wbcir_parse_rc6(struct device *dev, struct wbcir_data *data)
{
	/*
	 * Normal bits are manchester coded as follows:
	 * cell0 + cell1 = logic "0"
	 * cell1 + cell0 = logic "1"
	 *
	 * The IR pulse has the following components:
	 *
	 * Leader		- 6 * cell1 - discarded
	 * Gap    		- 2 * cell0 - discarded
	 * Start bit		- Normal Coding - always "1"
	 * Mode Bit 2 - 0	- Normal Coding
	 * Toggle bit		- Normal Coding with double bit time,
	 *			  e.g. cell0 + cell0 + cell1 + cell1
	 *			  means logic "0".
	 *
	 * The rest depends on the mode, the following modes are known:
	 *
	 * MODE 0:
	 *  Address Bit 7 - 0	- Normal Coding
	 *  Command Bit 7 - 0	- Normal Coding
	 *
	 * MODE 6:
	 *  The above Toggle Bit is used as a submode bit, 0 = A, 1 = B.
	 *  Submode B is for pointing devices, only remotes using submode A
	 *  are supported.
	 *
	 *  Customer range bit	- 0 => Customer = 7 bits, 0...127
	 *                        1 => Customer = 15 bits, 32768...65535
	 *  Customer Bits	- Normal Coding
	 *
	 *  Customer codes are allocated by Philips. The rest of the bits
	 *  are customer dependent. The following is commonly used (and the
	 *  only supported config):
	 *
	 *  Toggle Bit		- Normal Coding
	 *  Address Bit 6 - 0	- Normal Coding
	 *  Command Bit 7 - 0	- Normal Coding
	 *
	 * All modes are followed by at least 6 * cell0.
	 *
	 * MODE 0 msglen:
	 *  1 * 2 (start bit) + 3 * 2 (mode) + 2 * 2 (toggle) +
	 *  8 * 2 (address) + 8 * 2 (command) =
	 *  44 cells
	 *
	 * MODE 6A msglen:
	 *  1 * 2 (start bit) + 3 * 2 (mode) + 2 * 2 (submode) +
	 *  1 * 2 (customer range bit) + 7/15 * 2 (customer bits) +
	 *  1 * 2 (toggle bit) + 7 * 2 (address) + 8 * 2 (command) =
	 *  60 - 76 cells
	 */
	u8 mode;
	u8 toggle;
	u16 customer = 0x0;
	u8 address;
	u8 command;
	u32 scancode;

	/* Leader mark */
	while (get_bits(data, 1) && !data->irdata_error)
		/* Do nothing */;

	/* Leader space */
	if (get_bits(data, 1)) {
		dev_dbg(dev, "RC6 - Invalid leader space\n");
		return;
	}

	/* Start bit */
	if (get_bits(data, 2) != 0x02) {
		dev_dbg(dev, "RC6 - Invalid start bit\n");
		return;
	}

	/* Mode */
	mode = get_bits(data, 6);
	switch (mode) {
	case 0x15: /* 010101 = b000 */
		mode = 0;
		break;
	case 0x29: /* 101001 = b110 */
		mode = 6;
		break;
	default:
		dev_dbg(dev, "RC6 - Invalid mode\n");
		return;
	}

	/* Toggle bit / Submode bit */
	toggle = get_bits(data, 4);
	switch (toggle) {
	case 0x03:
		toggle = 0;
		break;
	case 0x0C:
		toggle = 1;
		break;
	default:
		dev_dbg(dev, "RC6 - Toggle bit error\n");
		break;
	}

	/* Customer */
	if (mode == 6) {
		if (toggle != 0) {
			dev_dbg(dev, "RC6B - Not Supported\n");
			return;
		}

		customer = wbcir_rc6cells_to_byte(data);

		if (customer & 0x80) {
			/* 15 bit customer value */
			customer <<= 8;
			customer |= wbcir_rc6cells_to_byte(data);
		}
	}

	/* Address */
	address = wbcir_rc6cells_to_byte(data);
	if (mode == 6) {
		toggle = address >> 7;
		address &= 0x7F;
	}

	/* Command */
	command = wbcir_rc6cells_to_byte(data);

	/* Create scancode */
	scancode =  command;
	scancode |= address << 8;
	scancode |= customer << 16;

	/* Last sanity check */
	if (data->irdata_error) {
		dev_dbg(dev, "RC6 - Cell error(s)\n");
		return;
	}

	dev_dbg(dev, "IR-RC6 ad 0x%02X cm 0x%02X cu 0x%04X "
		"toggle %u mode %u scan 0x%08X\n",
		address,
		command,
		customer,
		(unsigned int)toggle,
		(unsigned int)mode,
		scancode);

	wbcir_keydown(data, scancode, toggle);
}