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
struct saa7134_dev {int board; struct saa7134_card_ir* remote; } ;
struct saa7134_card_ir {int last_gpio; int mask_keycode; int mask_keydown; int mask_keyup; int /*<<< orphan*/  dev; scalar_t__ polling; } ;

/* Variables and functions */
#define  SAA7134_BOARD_GOTVIEW_7135 129 
#define  SAA7134_BOARD_KWORLD_PLUS_TV_ANALOG 128 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE3 ; 
 int SAA7134_GPIO_GPRESCAN ; 
 int SAA7134_GPIO_GPSTATUS0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS1 ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int) ; 
 int ir_extract_bits (int,int) ; 
 int /*<<< orphan*/  rc_keydown_notimeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keyup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_clearb (int /*<<< orphan*/ ,int) ; 
 int saa_readl (int) ; 
 int /*<<< orphan*/  saa_setb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int build_key(struct saa7134_dev *dev)
{
	struct saa7134_card_ir *ir = dev->remote;
	u32 gpio, data;

	/* here comes the additional handshake steps for some cards */
	switch (dev->board) {
	case SAA7134_BOARD_GOTVIEW_7135:
		saa_setb(SAA7134_GPIO_GPSTATUS1, 0x80);
		saa_clearb(SAA7134_GPIO_GPSTATUS1, 0x80);
		break;
	}
	/* rising SAA7134_GPIO_GPRESCAN reads the status */
	saa_clearb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPRESCAN);

	gpio = saa_readl(SAA7134_GPIO_GPSTATUS0 >> 2);
	if (ir->polling) {
		if (ir->last_gpio == gpio)
			return 0;
		ir->last_gpio = gpio;
	}

	data = ir_extract_bits(gpio, ir->mask_keycode);
	dprintk("build_key gpio=0x%x mask=0x%x data=%d\n",
		gpio, ir->mask_keycode, data);

	switch (dev->board) {
	case SAA7134_BOARD_KWORLD_PLUS_TV_ANALOG:
		if (data == ir->mask_keycode)
			rc_keyup(ir->dev);
		else
			rc_keydown_notimeout(ir->dev, data, 0);
		return 0;
	}

	if (ir->polling) {
		if ((ir->mask_keydown  &&  (0 != (gpio & ir->mask_keydown))) ||
		    (ir->mask_keyup    &&  (0 == (gpio & ir->mask_keyup)))) {
			rc_keydown_notimeout(ir->dev, data, 0);
		} else {
			rc_keyup(ir->dev);
		}
	}
	else {	/* IRQ driven mode - handle key press and release in one go */
		if ((ir->mask_keydown  &&  (0 != (gpio & ir->mask_keydown))) ||
		    (ir->mask_keyup    &&  (0 == (gpio & ir->mask_keyup)))) {
			rc_keydown_notimeout(ir->dev, data, 0);
			rc_keyup(ir->dev);
		}
	}

	return 0;
}