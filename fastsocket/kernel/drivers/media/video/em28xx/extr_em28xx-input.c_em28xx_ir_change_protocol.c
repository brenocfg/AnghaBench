#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct rc_dev {struct em28xx_IR* priv; } ;
struct em28xx_IR {int full_code; int /*<<< orphan*/  get_key; struct em28xx* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  xclk; } ;
struct em28xx {int chip_id; TYPE_1__ board; } ;

/* Variables and functions */
#define  CHIP_ID_EM2860 130 
#define  CHIP_ID_EM2874 129 
#define  CHIP_ID_EM2883 128 
 int EINVAL ; 
 int /*<<< orphan*/  EM2874_IR_NEC ; 
 int /*<<< orphan*/  EM2874_IR_RC5 ; 
 int /*<<< orphan*/  EM2874_R50_IR_CONFIG ; 
 int /*<<< orphan*/  EM28XX_R0F_XCLK ; 
 int /*<<< orphan*/  EM28XX_XCLK_IR_RC5_MODE ; 
 scalar_t__ RC_TYPE_NEC ; 
 scalar_t__ RC_TYPE_RC5 ; 
 scalar_t__ RC_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  default_polling_getkey ; 
 int /*<<< orphan*/  em2874_polling_getkey ; 
 int /*<<< orphan*/  em28xx_write_reg_bits (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_write_regs (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

int em28xx_ir_change_protocol(struct rc_dev *rc_dev, u64 rc_type)
{
	int rc = 0;
	struct em28xx_IR *ir = rc_dev->priv;
	struct em28xx *dev = ir->dev;
	u8 ir_config = EM2874_IR_RC5;

	/* Adjust xclk based o IR table for RC5/NEC tables */

	if (rc_type == RC_TYPE_RC5) {
		dev->board.xclk |= EM28XX_XCLK_IR_RC5_MODE;
		ir->full_code = 1;
	} else if (rc_type == RC_TYPE_NEC) {
		dev->board.xclk &= ~EM28XX_XCLK_IR_RC5_MODE;
		ir_config = EM2874_IR_NEC;
		ir->full_code = 1;
	} else if (rc_type != RC_TYPE_UNKNOWN)
		rc = -EINVAL;

	em28xx_write_reg_bits(dev, EM28XX_R0F_XCLK, dev->board.xclk,
			      EM28XX_XCLK_IR_RC5_MODE);

	/* Setup the proper handler based on the chip */
	switch (dev->chip_id) {
	case CHIP_ID_EM2860:
	case CHIP_ID_EM2883:
		ir->get_key = default_polling_getkey;
		break;
	case CHIP_ID_EM2874:
		ir->get_key = em2874_polling_getkey;
		em28xx_write_regs(dev, EM2874_R50_IR_CONFIG, &ir_config, 1);
		break;
	default:
		printk("Unrecognized em28xx chip id: IR not supported\n");
		rc = -EINVAL;
	}

	return rc;
}