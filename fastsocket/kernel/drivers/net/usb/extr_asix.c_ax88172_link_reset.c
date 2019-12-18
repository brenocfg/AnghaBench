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
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {int /*<<< orphan*/  mii; } ;
struct ethtool_cmd {scalar_t__ duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX88172_MEDIUM_DEFAULT ; 
 int /*<<< orphan*/  AX88172_MEDIUM_FD ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  asix_write_medium_mode (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 

__attribute__((used)) static int ax88172_link_reset(struct usbnet *dev)
{
	u8 mode;
	struct ethtool_cmd ecmd;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);
	mode = AX88172_MEDIUM_DEFAULT;

	if (ecmd.duplex != DUPLEX_FULL)
		mode |= ~AX88172_MEDIUM_FD;

	devdbg(dev, "ax88172_link_reset() speed: %d duplex: %d setting mode to 0x%04x", ecmd.speed, ecmd.duplex, mode);

	asix_write_medium_mode(dev, mode);

	return 0;
}