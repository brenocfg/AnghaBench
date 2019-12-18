#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u32 ;
struct saa7134_dev {int dummy; } ;
struct IR_i2c {TYPE_2__* c; } ;
struct TYPE_5__ {TYPE_1__* adapter; } ;
struct TYPE_4__ {struct saa7134_dev* algo_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE3 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPRESCAN ; 
 int SAA7134_GPIO_GPSTATUS0 ; 
 int i2c_master_recv (TYPE_2__*,unsigned char*,int) ; 
 int i2c_master_send (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  i2cdprintk (char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  saa_clearb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int saa_readl (int) ; 
 int /*<<< orphan*/  saa_setb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_key_flydvb_trio(struct IR_i2c *ir, u32 *ir_key, u32 *ir_raw)
{
	int gpio;
	int attempt = 0;
	unsigned char b;

	/* We need this to access GPI Used by the saa_readl macro. */
	struct saa7134_dev *dev = ir->c->adapter->algo_data;

	if (dev == NULL) {
		i2cdprintk("get_key_flydvb_trio: "
			   "ir->c->adapter->algo_data is NULL!\n");
		return -EIO;
	}

	/* rising SAA7134_GPIGPRESCAN reads the status */
	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);

	gpio = saa_readl(SAA7134_GPIO_GPSTATUS0 >> 2);

	if (0x40000 & ~gpio)
		return 0; /* No button press */

	/* No button press - only before first key pressed */
	if (b == 0xFF)
		return 0;

	/* poll IR chip */
	/* weak up the IR chip */
	b = 0;

	while (1 != i2c_master_send(ir->c, &b, 1)) {
		if ((attempt++) < 10) {
			/*
			 * wait a bit for next attempt -
			 * I don't know how make it better
			 */
			msleep(10);
			continue;
		}
		i2cdprintk("send wake up byte to pic16C505 (IR chip)"
			   "failed %dx\n", attempt);
		return -EIO;
	}
	if (1 != i2c_master_recv(ir->c, &b, 1)) {
		i2cdprintk("read error\n");
		return -EIO;
	}

	*ir_key = b;
	*ir_raw = b;
	return 1;
}