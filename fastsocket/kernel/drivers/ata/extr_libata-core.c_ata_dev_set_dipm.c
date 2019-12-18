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
typedef  int u32 ;
struct ata_port {int flags; int pm_policy; } ;
struct ata_link {struct ata_port* ap; } ;
struct ata_device {int flags; struct ata_link* link; } ;
typedef  enum link_pm { ____Placeholder_link_pm } link_pm ;

/* Variables and functions */
 int ATA_DFLAG_DIPM ; 
 int ATA_FLAG_IPM ; 
 int EINVAL ; 
#define  MAX_PERFORMANCE 131 
#define  MEDIUM_POWER 130 
#define  MIN_POWER 129 
#define  NOT_AVAILABLE 128 
 int /*<<< orphan*/  SATA_DIPM ; 
 int /*<<< orphan*/  SCR_CONTROL ; 
 int /*<<< orphan*/  SETFEATURES_SATA_ENABLE ; 
 int /*<<< orphan*/  ata_dev_enabled (struct ata_device*) ; 
 unsigned int ata_dev_set_feature (struct ata_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sata_scr_read (struct ata_link*,int /*<<< orphan*/ ,int*) ; 
 int sata_scr_write (struct ata_link*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ata_dev_set_dipm(struct ata_device *dev, enum link_pm policy)
{
	struct ata_link *link = dev->link;
	struct ata_port *ap = link->ap;
	u32 scontrol;
	unsigned int err_mask;
	int rc;

	/*
	 * disallow DIPM for drivers which haven't set
	 * ATA_FLAG_IPM.  This is because when DIPM is enabled,
	 * phy ready will be set in the interrupt status on
	 * state changes, which will cause some drivers to
	 * think there are errors - additionally drivers will
	 * need to disable hot plug.
	 */
	if (!(ap->flags & ATA_FLAG_IPM) || !ata_dev_enabled(dev)) {
		ap->pm_policy = NOT_AVAILABLE;
		return -EINVAL;
	}

	/*
	 * For DIPM, we will only enable it for the
	 * min_power setting.
	 *
	 * Why?  Because Disks are too stupid to know that
	 * If the host rejects a request to go to SLUMBER
	 * they should retry at PARTIAL, and instead it
	 * just would give up.  So, for medium_power to
	 * work at all, we need to only allow HIPM.
	 */
	rc = sata_scr_read(link, SCR_CONTROL, &scontrol);
	if (rc)
		return rc;

	switch (policy) {
	case MIN_POWER:
		/* no restrictions on IPM transitions */
		scontrol &= ~(0x3 << 8);
		rc = sata_scr_write(link, SCR_CONTROL, scontrol);
		if (rc)
			return rc;

		/* enable DIPM */
		if (dev->flags & ATA_DFLAG_DIPM)
			err_mask = ata_dev_set_feature(dev,
					SETFEATURES_SATA_ENABLE, SATA_DIPM);
		break;
	case MEDIUM_POWER:
		/* allow IPM to PARTIAL */
		scontrol &= ~(0x1 << 8);
		scontrol |= (0x2 << 8);
		rc = sata_scr_write(link, SCR_CONTROL, scontrol);
		if (rc)
			return rc;

		/*
		 * we don't have to disable DIPM since IPM flags
		 * disallow transitions to SLUMBER, which effectively
		 * disable DIPM if it does not support PARTIAL
		 */
		break;
	case NOT_AVAILABLE:
	case MAX_PERFORMANCE:
		/* disable all IPM transitions */
		scontrol |= (0x3 << 8);
		rc = sata_scr_write(link, SCR_CONTROL, scontrol);
		if (rc)
			return rc;

		/*
		 * we don't have to disable DIPM since IPM flags
		 * disallow all transitions which effectively
		 * disable DIPM anyway.
		 */
		break;
	}

	/* FIXME: handle SET FEATURES failure */
	(void) err_mask;

	return 0;
}