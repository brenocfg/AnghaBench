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
typedef  int u32 ;
struct cx88_core {int boardnr; } ;
struct cx88_IR {int last_gpio; int mask_keydown; int mask_keyup; int /*<<< orphan*/  dev; struct cx88_core* core; scalar_t__ polling; int /*<<< orphan*/  mask_keycode; int /*<<< orphan*/  gpio_addr; } ;

/* Variables and functions */
 scalar_t__ CX88_BOARD_NORWOOD_MICRO ; 
#define  CX88_BOARD_NPGTECH_REALTV_TOP10FM 131 
#define  CX88_BOARD_WINFAST_DTV1000 130 
#define  CX88_BOARD_WINFAST_DTV1800H 129 
#define  CX88_BOARD_WINFAST_TV2000_XP_GLOBAL 128 
 int /*<<< orphan*/  MO_GP0_IO ; 
 int /*<<< orphan*/  MO_GP1_IO ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_dprintk (char*,int,int,char*,char*,char*) ; 
 int ir_extract_bits (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keydown_notimeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keyup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx88_ir_handle_key(struct cx88_IR *ir)
{
	struct cx88_core *core = ir->core;
	u32 gpio, data, auxgpio;

	/* read gpio value */
	gpio = cx_read(ir->gpio_addr);
	switch (core->boardnr) {
	case CX88_BOARD_NPGTECH_REALTV_TOP10FM:
		/* This board apparently uses a combination of 2 GPIO
		   to represent the keys. Additionally, the second GPIO
		   can be used for parity.

		   Example:

		   for key "5"
			gpio = 0x758, auxgpio = 0xe5 or 0xf5
		   for key "Power"
			gpio = 0x758, auxgpio = 0xed or 0xfd
		 */

		auxgpio = cx_read(MO_GP1_IO);
		/* Take out the parity part */
		gpio=(gpio & 0x7fd) + (auxgpio & 0xef);
		break;
	case CX88_BOARD_WINFAST_DTV1000:
	case CX88_BOARD_WINFAST_DTV1800H:
	case CX88_BOARD_WINFAST_TV2000_XP_GLOBAL:
		gpio = (gpio & 0x6ff) | ((cx_read(MO_GP1_IO) << 8) & 0x900);
		auxgpio = gpio;
		break;
	default:
		auxgpio = gpio;
	}
	if (ir->polling) {
		if (ir->last_gpio == auxgpio)
			return;
		ir->last_gpio = auxgpio;
	}

	/* extract data */
	data = ir_extract_bits(gpio, ir->mask_keycode);
	ir_dprintk("irq gpio=0x%x code=%d | %s%s%s\n",
		   gpio, data,
		   ir->polling ? "poll" : "irq",
		   (gpio & ir->mask_keydown) ? " down" : "",
		   (gpio & ir->mask_keyup) ? " up" : "");

	if (ir->core->boardnr == CX88_BOARD_NORWOOD_MICRO) {
		u32 gpio_key = cx_read(MO_GP0_IO);

		data = (data << 4) | ((gpio_key & 0xf0) >> 4);

		rc_keydown(ir->dev, data, 0);

	} else if (ir->mask_keydown) {
		/* bit set on keydown */
		if (gpio & ir->mask_keydown)
			rc_keydown_notimeout(ir->dev, data, 0);
		else
			rc_keyup(ir->dev);

	} else if (ir->mask_keyup) {
		/* bit cleared on keydown */
		if (0 == (gpio & ir->mask_keyup))
			rc_keydown_notimeout(ir->dev, data, 0);
		else
			rc_keyup(ir->dev);

	} else {
		/* can't distinguish keydown/up :-/ */
		rc_keydown_notimeout(ir->dev, data, 0);
		rc_keyup(ir->dev);
	}
}