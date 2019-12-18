#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u32 ;
struct saa7134_dev {int dummy; } ;
struct IR_i2c {TYPE_2__* c; } ;
struct TYPE_4__ {TYPE_1__* adapter; } ;
struct TYPE_3__ {struct saa7134_dev* algo_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE3 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPRESCAN ; 
 int SAA7134_GPIO_GPSTATUS0 ; 
 int /*<<< orphan*/  dprintk (char*,unsigned char) ; 
 int i2c_master_recv (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  i2cdprintk (char*) ; 
 int /*<<< orphan*/  saa_clearb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int saa_readl (int) ; 
 int /*<<< orphan*/  saa_setb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_key_msi_tvanywhere_plus(struct IR_i2c *ir, u32 *ir_key,
				       u32 *ir_raw)
{
	unsigned char b;
	int gpio;

	/* <dev> is needed to access GPIO. Used by the saa_readl macro. */
	struct saa7134_dev *dev = ir->c->adapter->algo_data;
	if (dev == NULL) {
		i2cdprintk("get_key_msi_tvanywhere_plus: "
			   "ir->c->adapter->algo_data is NULL!\n");
		return -EIO;
	}

	/* rising SAA7134_GPIO_GPRESCAN reads the status */

	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);

	gpio = saa_readl(SAA7134_GPIO_GPSTATUS0 >> 2);

	/* GPIO&0x40 is pulsed low when a button is pressed. Don't do
	   I2C receive if gpio&0x40 is not low. */

	if (gpio & 0x40)
		return 0;       /* No button press */

	/* GPIO says there is a button press. Get it. */

	if (1 != i2c_master_recv(ir->c, &b, 1)) {
		i2cdprintk("read error\n");
		return -EIO;
	}

	/* No button press */

	if (b == 0xff)
		return 0;

	/* Button pressed */

	dprintk("get_key_msi_tvanywhere_plus: Key = 0x%02X\n", b);
	*ir_key = b;
	*ir_raw = b;
	return 1;
}