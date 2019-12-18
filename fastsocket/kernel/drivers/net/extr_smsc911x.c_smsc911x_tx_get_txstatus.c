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
struct smsc911x_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_FIFO_INF ; 
 unsigned int TX_FIFO_INF_TSUSED_ ; 
 int /*<<< orphan*/  TX_STATUS_FIFO ; 
 unsigned int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int smsc911x_tx_get_txstatus(struct smsc911x_data *pdata)
{
	unsigned int result =
	    smsc911x_reg_read(pdata, TX_FIFO_INF) & TX_FIFO_INF_TSUSED_;

	if (result != 0)
		result = smsc911x_reg_read(pdata, TX_STATUS_FIFO);

	return result;
}