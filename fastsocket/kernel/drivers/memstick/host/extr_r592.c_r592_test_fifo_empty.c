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
struct r592_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  R592_REG_MSC ; 
 int R592_REG_MSC_FIFO_EMPTY ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  message (char*) ; 
 int /*<<< orphan*/  r592_host_reset (struct r592_device*) ; 
 int r592_read_reg (struct r592_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r592_test_fifo_empty(struct r592_device *dev)
{
	if (r592_read_reg(dev, R592_REG_MSC) & R592_REG_MSC_FIFO_EMPTY)
		return 0;

	dbg("FIFO not ready, trying to reset the device");
	r592_host_reset(dev);

	if (r592_read_reg(dev, R592_REG_MSC) & R592_REG_MSC_FIFO_EMPTY)
		return 0;

	message("FIFO still not ready, giving up");
	return -EIO;
}