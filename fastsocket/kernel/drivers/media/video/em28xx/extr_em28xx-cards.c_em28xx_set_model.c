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
struct TYPE_2__ {int xclk; int i2c_speed; } ;
struct em28xx {size_t model; TYPE_1__ board; } ;

/* Variables and functions */
 int EM28XX_I2C_CLK_WAIT_ENABLE ; 
 int EM28XX_I2C_FREQ_100_KHZ ; 
 int EM28XX_XCLK_FREQUENCY_12MHZ ; 
 int EM28XX_XCLK_IR_RC5_MODE ; 
 int /*<<< orphan*/ * em28xx_boards ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void em28xx_set_model(struct em28xx *dev)
{
	memcpy(&dev->board, &em28xx_boards[dev->model], sizeof(dev->board));

	/* Those are the default values for the majority of boards
	   Use those values if not specified otherwise at boards entry
	 */
	if (!dev->board.xclk)
		dev->board.xclk = EM28XX_XCLK_IR_RC5_MODE |
				  EM28XX_XCLK_FREQUENCY_12MHZ;

	if (!dev->board.i2c_speed)
		dev->board.i2c_speed = EM28XX_I2C_CLK_WAIT_ENABLE |
				       EM28XX_I2C_FREQ_100_KHZ;
}