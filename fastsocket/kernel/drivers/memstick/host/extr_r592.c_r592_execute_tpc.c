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
typedef  int u32 ;
struct r592_device {TYPE_2__* req; scalar_t__ parallel_mode; } ;
struct TYPE_3__ {int length; } ;
struct TYPE_4__ {int tpc; int data_len; int error; int /*<<< orphan*/  int_reg; scalar_t__ need_card_int; TYPE_1__ sg; scalar_t__ long_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOSYS ; 
 int /*<<< orphan*/  MEMSTICK_INT_BREQ ; 
 int /*<<< orphan*/  MEMSTICK_INT_CED ; 
 int /*<<< orphan*/  MEMSTICK_INT_CMDNAK ; 
 int /*<<< orphan*/  MEMSTICK_INT_ERR ; 
 int MS_TPC_SET_RW_REG_ADRS ; 
 int /*<<< orphan*/  R592_IO ; 
 int /*<<< orphan*/  R592_IO_DIRECTION ; 
 int R592_LFIFO_SIZE ; 
 int /*<<< orphan*/  R592_REG_MSC ; 
 int /*<<< orphan*/  R592_REG_MSC_LED ; 
 int R592_REG_MSC_PRSNT ; 
 int /*<<< orphan*/  R592_STATUS ; 
 int R592_STATUS_CED ; 
 int R592_STATUS_P_BREQ ; 
 int R592_STATUS_P_CED ; 
 int R592_STATUS_P_CMDNACK ; 
 int R592_STATUS_P_INTERR ; 
 int R592_STATUS_RDY ; 
 int /*<<< orphan*/  R592_TPC_EXEC ; 
 int R592_TPC_EXEC_BIG_FIFO ; 
 int R592_TPC_EXEC_LEN_SHIFT ; 
 int R592_TPC_EXEC_TPC_SHIFT ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  memstick_debug_get_tpc_name (int) ; 
 int /*<<< orphan*/  message (char*) ; 
 int /*<<< orphan*/  r592_clear_reg_mask (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r592_read_reg (struct r592_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_set_reg_mask (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r592_test_fifo_empty (struct r592_device*) ; 
 int r592_test_io_error (struct r592_device*) ; 
 int r592_transfer_fifo_dma (struct r592_device*) ; 
 int r592_transfer_fifo_pio (struct r592_device*) ; 
 int r592_wait_status (struct r592_device*,int,int) ; 
 int /*<<< orphan*/  r592_write_reg (struct r592_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r592_execute_tpc(struct r592_device *dev)
{
	bool is_write = dev->req->tpc >= MS_TPC_SET_RW_REG_ADRS;
	int len, error;
	u32 status, reg;

	if (!dev->req) {
		message("BUG: tpc execution without request!");
		return;
	}

	len = dev->req->long_data ?
		dev->req->sg.length : dev->req->data_len;

	/* Ensure that FIFO can hold the input data */
	if (len > R592_LFIFO_SIZE) {
		message("IO: hardware doesn't support TPCs longer that 512");
		error = -ENOSYS;
		goto out;
	}

	if (!(r592_read_reg(dev, R592_REG_MSC) & R592_REG_MSC_PRSNT)) {
		dbg("IO: refusing to send TPC because card is absent");
		error = -ENODEV;
		goto out;
	}

	dbg("IO: executing %s LEN=%d",
			memstick_debug_get_tpc_name(dev->req->tpc), len);

	/* Set IO direction */
	if (is_write)
		r592_set_reg_mask(dev, R592_IO, R592_IO_DIRECTION);
	else
		r592_clear_reg_mask(dev, R592_IO, R592_IO_DIRECTION);


	error = r592_test_fifo_empty(dev);
	if (error)
		goto out;

	/* Transfer write data */
	if (is_write) {
		error = r592_transfer_fifo_dma(dev);
		if (error == -EINVAL)
			error = r592_transfer_fifo_pio(dev);
	}

	if (error)
		goto out;

	/* Trigger the TPC */
	reg = (len << R592_TPC_EXEC_LEN_SHIFT) |
		(dev->req->tpc << R592_TPC_EXEC_TPC_SHIFT) |
			R592_TPC_EXEC_BIG_FIFO;

	r592_write_reg(dev, R592_TPC_EXEC, reg);

	/* Wait for TPC completion */
	status = R592_STATUS_RDY;
	if (dev->req->need_card_int)
		status |= R592_STATUS_CED;

	error = r592_wait_status(dev, status, status);
	if (error) {
		message("card didn't respond");
		goto out;
	}

	/* Test IO errors */
	error = r592_test_io_error(dev);
	if (error) {
		dbg("IO error");
		goto out;
	}

	/* Read data from FIFO */
	if (!is_write) {
		error = r592_transfer_fifo_dma(dev);
		if (error == -EINVAL)
			error = r592_transfer_fifo_pio(dev);
	}

	/* read INT reg. This can be shortened with shifts, but that way
		its more readable */
	if (dev->parallel_mode && dev->req->need_card_int) {

		dev->req->int_reg = 0;
		status = r592_read_reg(dev, R592_STATUS);

		if (status & R592_STATUS_P_CMDNACK)
			dev->req->int_reg |= MEMSTICK_INT_CMDNAK;
		if (status & R592_STATUS_P_BREQ)
			dev->req->int_reg |= MEMSTICK_INT_BREQ;
		if (status & R592_STATUS_P_INTERR)
			dev->req->int_reg |= MEMSTICK_INT_ERR;
		if (status & R592_STATUS_P_CED)
			dev->req->int_reg |= MEMSTICK_INT_CED;
	}

	if (error)
		dbg("FIFO read error");
out:
	dev->req->error = error;
	r592_clear_reg_mask(dev, R592_REG_MSC, R592_REG_MSC_LED);
	return;
}