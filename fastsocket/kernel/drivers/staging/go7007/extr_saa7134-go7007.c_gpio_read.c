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
 int GPIO_COMMAND_READ ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE3 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPRESCAN ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS2 ; 
 int /*<<< orphan*/  saa_clearb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_setb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gpio_read(struct saa7134_dev *dev, u8 addr, u16 *data)
{
	saa_writeb(SAA7134_GPIO_GPMODE0, 0xff);

	/* Write HPI address */
	saa_writeb(SAA7134_GPIO_GPSTATUS0, addr);
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDR);
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	saa_writeb(SAA7134_GPIO_GPMODE0, 0x00);

	/* Read low byte */
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_READ);
	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	*data = saa_readb(SAA7134_GPIO_GPSTATUS0);
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	/* Read high byte */
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_READ);
	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	*data |= saa_readb(SAA7134_GPIO_GPSTATUS0) << 8;
	saa_writeb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	return 0;
}