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
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_CMD_WRITE_RX_CTL ; 
 int asix_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deverr (struct usbnet*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int asix_write_rx_ctl(struct usbnet *dev, u16 mode)
{
	int ret;

	devdbg(dev,"asix_write_rx_ctl() - mode = 0x%04x", mode);
	ret = asix_write_cmd(dev, AX_CMD_WRITE_RX_CTL, mode, 0, 0, NULL);
	if (ret < 0)
		deverr(dev, "Failed to write RX_CTL mode to 0x%04x: %02x",
		       mode, ret);

	return ret;
}