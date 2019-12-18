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
struct usbnet {int /*<<< orphan*/  mii; int /*<<< orphan*/  data; } ;
struct ethtool_cmd {scalar_t__ speed; scalar_t__ duplex; } ;
struct asix_data {scalar_t__ phymode; scalar_t__ ledmode; } ;

/* Variables and functions */
 int AX88178_MEDIUM_DEFAULT ; 
 int AX_MEDIUM_ENCK ; 
 int AX_MEDIUM_FD ; 
 int AX_MEDIUM_GM ; 
 int AX_MEDIUM_PS ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ PHY_MODE_MARVELL ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  asix_write_medium_mode (struct usbnet*,int) ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,...) ; 
 int /*<<< orphan*/  marvell_led_status (struct usbnet*,scalar_t__) ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 

__attribute__((used)) static int ax88178_link_reset(struct usbnet *dev)
{
	u16 mode;
	struct ethtool_cmd ecmd;
	struct asix_data *data = (struct asix_data *)&dev->data;

	devdbg(dev,"ax88178_link_reset()");

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);
	mode = AX88178_MEDIUM_DEFAULT;

	if (ecmd.speed == SPEED_1000)
		mode |= AX_MEDIUM_GM;
	else if (ecmd.speed == SPEED_100)
		mode |= AX_MEDIUM_PS;
	else
		mode &= ~(AX_MEDIUM_PS | AX_MEDIUM_GM);

	mode |= AX_MEDIUM_ENCK;

	if (ecmd.duplex == DUPLEX_FULL)
		mode |= AX_MEDIUM_FD;
	else
		mode &= ~AX_MEDIUM_FD;

	devdbg(dev, "ax88178_link_reset() speed: %d duplex: %d setting mode to 0x%04x", ecmd.speed, ecmd.duplex, mode);

	asix_write_medium_mode(dev, mode);

	if (data->phymode == PHY_MODE_MARVELL && data->ledmode)
		marvell_led_status(dev, ecmd.speed);

	return 0;
}