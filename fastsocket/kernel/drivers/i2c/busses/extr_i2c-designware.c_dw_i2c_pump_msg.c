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
typedef  int u16 ;
struct dw_i2c_dev {int status; scalar_t__ base; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 scalar_t__ DW_IC_INTR_MASK ; 
 int DW_IC_INTR_STOP_DET ; 
 int DW_IC_INTR_TX_ABRT ; 
 int DW_IC_INTR_TX_EMPTY ; 
 int STATUS_WRITE_IN_PROGRESS ; 
 int /*<<< orphan*/  i2c_dw_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_dw_xfer_msg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void dw_i2c_pump_msg(unsigned long data)
{
	struct dw_i2c_dev *dev = (struct dw_i2c_dev *) data;
	u16 intr_mask;

	i2c_dw_read(&dev->adapter);
	i2c_dw_xfer_msg(&dev->adapter);

	intr_mask = DW_IC_INTR_STOP_DET | DW_IC_INTR_TX_ABRT;
	if (dev->status & STATUS_WRITE_IN_PROGRESS)
		intr_mask |= DW_IC_INTR_TX_EMPTY;
	writew(intr_mask, dev->base + DW_IC_INTR_MASK);
}