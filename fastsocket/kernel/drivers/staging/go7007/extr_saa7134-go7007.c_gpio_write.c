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
typedef  int u16 ;
struct saa7134_dev {int dummy; } ;

/* Variables and functions */
 int GPIO_COMMAND_ADDR ; 
 int GPIO_COMMAND_IDLE ; 
 int GPIO_COMMAND_WRITE ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS2 ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gpio_write(struct saa7134_dev *dev, u8 addr, u16 data)
{
	saa_writeb(SAA7134_GPIO_GPMODE0, 0xff);

	/* Write HPI address */
	saa_writeb(SAA7134_GPIO_GPSTATUS0, addr);
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDR);
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	/* Write low byte */
	saa_writeb(SAA7134_GPIO_GPSTATUS0, data & 0xff);
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WRITE);
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	/* Write high byte */
	saa_writeb(SAA7134_GPIO_GPSTATUS0, data >> 8);
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WRITE);
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	return 0;
}