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
struct usbnet {int /*<<< orphan*/  mii; } ;
struct ethtool_cmd {scalar_t__ speed; scalar_t__ duplex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX88772_MEDIUM_DEFAULT ; 
 int /*<<< orphan*/  AX_MEDIUM_FD ; 
 int /*<<< orphan*/  AX_MEDIUM_PS ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  asix_write_medium_mode (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 

__attribute__((used)) static int ax88772_link_reset(struct usbnet *dev)
{
	u16 mode;
	struct ethtool_cmd ecmd;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);
	mode = AX88772_MEDIUM_DEFAULT;

	if (ecmd.speed != SPEED_100)
		mode &= ~AX_MEDIUM_PS;

	if (ecmd.duplex != DUPLEX_FULL)
		mode &= ~AX_MEDIUM_FD;

	devdbg(dev, "ax88772_link_reset() speed: %d duplex: %d setting mode to 0x%04x", ecmd.speed, ecmd.duplex, mode);

	asix_write_medium_mode(dev, mode);

	return 0;
}