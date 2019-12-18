#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  head; } ;
struct TYPE_9__ {int bits; } ;
struct TYPE_8__ {unsigned int bits; } ;
struct TYPE_11__ {TYPE_3__ min_turn_time; TYPE_2__ baud_rate; } ;
struct sa1100_irda {TYPE_4__ rx_buff; TYPE_4__ tx_buff; int /*<<< orphan*/  utcr4; TYPE_5__ qos; scalar_t__ pdata; TYPE_1__* dev; } ;
struct TYPE_7__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  HSCR0_UART ; 
 int /*<<< orphan*/  IRQ_Ser2ICP ; 
 unsigned int IR_115200 ; 
 unsigned int IR_19200 ; 
 unsigned int IR_38400 ; 
 int IR_4000000 ; 
 unsigned int IR_57600 ; 
 unsigned int IR_9600 ; 
 int /*<<< orphan*/  Ser2HSCR0 ; 
 int /*<<< orphan*/  Ser2HSCR2 ; 
 int /*<<< orphan*/  Ser2UTCR0 ; 
 scalar_t__ Ser2UTCR3 ; 
 int /*<<< orphan*/  Ser2UTCR4 ; 
 int /*<<< orphan*/  UTCR4_HPSIR ; 
 int /*<<< orphan*/  UTCR4_Z1_6us ; 
 int /*<<< orphan*/  __PREG (int /*<<< orphan*/ ) ; 
 struct net_device* alloc_irdadev (int) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  irda_init_max_qos_capabilies (TYPE_5__*) ; 
 int /*<<< orphan*/  irda_qos_bits_to_value (TYPE_5__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int max_rate ; 
 struct sa1100_irda* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 scalar_t__ request_mem_region (int /*<<< orphan*/ ,int,char*) ; 
 int sa1100_irda_init_iobuf (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sa1100_irda_netdev_ops ; 
 scalar_t__ tx_lpm ; 

__attribute__((used)) static int sa1100_irda_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct sa1100_irda *si;
	unsigned int baudrate_mask;
	int err;

	if (!pdev->dev.platform_data)
		return -EINVAL;

	err = request_mem_region(__PREG(Ser2UTCR0), 0x24, "IrDA") ? 0 : -EBUSY;
	if (err)
		goto err_mem_1;
	err = request_mem_region(__PREG(Ser2HSCR0), 0x1c, "IrDA") ? 0 : -EBUSY;
	if (err)
		goto err_mem_2;
	err = request_mem_region(__PREG(Ser2HSCR2), 0x04, "IrDA") ? 0 : -EBUSY;
	if (err)
		goto err_mem_3;

	dev = alloc_irdadev(sizeof(struct sa1100_irda));
	if (!dev)
		goto err_mem_4;

	si = netdev_priv(dev);
	si->dev = &pdev->dev;
	si->pdata = pdev->dev.platform_data;

	/*
	 * Initialise the HP-SIR buffers
	 */
	err = sa1100_irda_init_iobuf(&si->rx_buff, 14384);
	if (err)
		goto err_mem_5;
	err = sa1100_irda_init_iobuf(&si->tx_buff, 4000);
	if (err)
		goto err_mem_5;

	dev->netdev_ops	= &sa1100_irda_netdev_ops;
	dev->irq	= IRQ_Ser2ICP;

	irda_init_max_qos_capabilies(&si->qos);

	/*
	 * We support original IRDA up to 115k2. (we don't currently
	 * support 4Mbps).  Min Turn Time set to 1ms or greater.
	 */
	baudrate_mask = IR_9600;

	switch (max_rate) {
	case 4000000:		baudrate_mask |= IR_4000000 << 8;
	case 115200:		baudrate_mask |= IR_115200;
	case 57600:		baudrate_mask |= IR_57600;
	case 38400:		baudrate_mask |= IR_38400;
	case 19200:		baudrate_mask |= IR_19200;
	}
		
	si->qos.baud_rate.bits &= baudrate_mask;
	si->qos.min_turn_time.bits = 7;

	irda_qos_bits_to_value(&si->qos);

	si->utcr4 = UTCR4_HPSIR;
	if (tx_lpm)
		si->utcr4 |= UTCR4_Z1_6us;

	/*
	 * Initially enable HP-SIR modulation, and ensure that the port
	 * is disabled.
	 */
	Ser2UTCR3 = 0;
	Ser2UTCR4 = si->utcr4;
	Ser2HSCR0 = HSCR0_UART;

	err = register_netdev(dev);
	if (err == 0)
		platform_set_drvdata(pdev, dev);

	if (err) {
 err_mem_5:
		kfree(si->tx_buff.head);
		kfree(si->rx_buff.head);
		free_netdev(dev);
 err_mem_4:
		release_mem_region(__PREG(Ser2HSCR2), 0x04);
 err_mem_3:
		release_mem_region(__PREG(Ser2HSCR0), 0x1c);
 err_mem_2:
		release_mem_region(__PREG(Ser2UTCR0), 0x24);
	}
 err_mem_1:
	return err;
}