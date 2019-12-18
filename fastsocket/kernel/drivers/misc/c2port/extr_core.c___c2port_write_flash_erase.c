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
typedef  scalar_t__ u8 ;
struct c2port_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ C2PORT_COMMAND_OK ; 
 int C2PORT_DEVICE_ERASE ; 
 int /*<<< orphan*/  C2PORT_FPDAT ; 
 int EBUSY ; 
 int c2port_poll_in_busy (struct c2port_device*) ; 
 int c2port_poll_out_ready (struct c2port_device*) ; 
 int c2port_read_dr (struct c2port_device*,scalar_t__*) ; 
 int /*<<< orphan*/  c2port_write_ar (struct c2port_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2port_write_dr (struct c2port_device*,int) ; 

__attribute__((used)) static ssize_t __c2port_write_flash_erase(struct c2port_device *dev)
{
	u8 status;
	int ret;

	/* Target the C2 flash programming data register for C2 data register
	 * access.
	 */
	c2port_write_ar(dev, C2PORT_FPDAT);

	/* Send device erase command */
	c2port_write_dr(dev, C2PORT_DEVICE_ERASE);

	/* Wait for input acknowledge */
	ret = c2port_poll_in_busy(dev);
	if (ret < 0)
		return ret;

	/* Should check status before starting FLASH access sequence */

	/* Wait for status information */
	ret = c2port_poll_out_ready(dev);
	if (ret < 0)
		return ret;

	/* Read flash programming interface status */
	ret = c2port_read_dr(dev, &status);
	if (ret < 0)
		return ret;
	if (status != C2PORT_COMMAND_OK)
		return -EBUSY;

	/* Send a three-byte arming sequence to enable the device erase.
	 * If the sequence is not received correctly, the command will be
	 * ignored.
	 * Sequence is: 0xde, 0xad, 0xa5.
	 */
	c2port_write_dr(dev, 0xde);
	ret = c2port_poll_in_busy(dev);
	if (ret < 0)
		return ret;
	c2port_write_dr(dev, 0xad);
	ret = c2port_poll_in_busy(dev);
	if (ret < 0)
		return ret;
	c2port_write_dr(dev, 0xa5);
	ret = c2port_poll_in_busy(dev);
	if (ret < 0)
		return ret;

	ret = c2port_poll_out_ready(dev);
	if (ret < 0)
		return ret;

	return 0;
}