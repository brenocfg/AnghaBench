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
struct adapter {int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_REG (int,int /*<<< orphan*/ ) ; 
 int RXFIFO_PRTY_ERR ; 
 int TXFIFO_PRTY_ERR ; 
 int /*<<< orphan*/  XGMAC_PORT_INT_CAUSE ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  t4_fatal_err (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgmac_intr_handler(struct adapter *adap, int port)
{
	u32 v = t4_read_reg(adap, PORT_REG(port, XGMAC_PORT_INT_CAUSE));

	v &= TXFIFO_PRTY_ERR | RXFIFO_PRTY_ERR;
	if (!v)
		return;

	if (v & TXFIFO_PRTY_ERR)
		dev_alert(adap->pdev_dev, "XGMAC %d Tx FIFO parity error\n",
			  port);
	if (v & RXFIFO_PRTY_ERR)
		dev_alert(adap->pdev_dev, "XGMAC %d Rx FIFO parity error\n",
			  port);
	t4_write_reg(adap, PORT_REG(port, XGMAC_PORT_INT_CAUSE), v);
	t4_fatal_err(adap);
}