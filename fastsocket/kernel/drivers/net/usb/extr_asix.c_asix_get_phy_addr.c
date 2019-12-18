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
typedef  int u8 ;
struct usbnet {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  AX_CMD_READ_PHY_ID ; 
 int asix_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,...) ; 
 int /*<<< orphan*/  deverr (struct usbnet*,char*,int) ; 

__attribute__((used)) static inline int asix_get_phy_addr(struct usbnet *dev)
{
	u8 buf[2];
	int ret = asix_read_cmd(dev, AX_CMD_READ_PHY_ID, 0, 0, 2, buf);

	devdbg(dev, "asix_get_phy_addr()");

	if (ret < 0) {
		deverr(dev, "Error reading PHYID register: %02x", ret);
		goto out;
	}
	devdbg(dev, "asix_get_phy_addr() returning 0x%04x", *((__le16 *)buf));
	ret = buf[1];

out:
	return ret;
}