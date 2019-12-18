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
struct ata_link {int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_TMOUT_PMP_SRST_WAIT ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  SCR_CONTROL ; 
 unsigned long ata_deadline (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ata_is_host_link (struct ata_link*) ; 
 int /*<<< orphan*/  ata_link_printk (struct ata_link*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ata_msleep (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ata_phys_link_offline (struct ata_link*) ; 
 int ata_wait_ready (struct ata_link*,unsigned long,int (*) (struct ata_link*)) ; 
 int /*<<< orphan*/  jiffies ; 
 int sata_link_resume (struct ata_link*,unsigned long const*,unsigned long) ; 
 scalar_t__ sata_pmp_supported (int /*<<< orphan*/ ) ; 
 int sata_scr_read (struct ata_link*,int /*<<< orphan*/ ,int*) ; 
 int sata_scr_write (struct ata_link*,int /*<<< orphan*/ ,int) ; 
 int sata_scr_write_flush (struct ata_link*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sata_set_spd (struct ata_link*) ; 
 scalar_t__ sata_set_spd_needed (struct ata_link*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int sata_link_hardreset(struct ata_link *link, const unsigned long *timing,
			unsigned long deadline,
			bool *online, int (*check_ready)(struct ata_link *))
{
	u32 scontrol;
	int rc;

	DPRINTK("ENTER\n");

	if (online)
		*online = false;

	if (sata_set_spd_needed(link)) {
		/* SATA spec says nothing about how to reconfigure
		 * spd.  To be on the safe side, turn off phy during
		 * reconfiguration.  This works for at least ICH7 AHCI
		 * and Sil3124.
		 */
		if ((rc = sata_scr_read(link, SCR_CONTROL, &scontrol)))
			goto out;

		scontrol = (scontrol & 0x0f0) | 0x304;

		if ((rc = sata_scr_write(link, SCR_CONTROL, scontrol)))
			goto out;

		sata_set_spd(link);
	}

	/* issue phy wake/reset */
	if ((rc = sata_scr_read(link, SCR_CONTROL, &scontrol)))
		goto out;

	scontrol = (scontrol & 0x0f0) | 0x301;

	if ((rc = sata_scr_write_flush(link, SCR_CONTROL, scontrol)))
		goto out;

	/* Couldn't find anything in SATA I/II specs, but AHCI-1.1
	 * 10.4.2 says at least 1 ms.
	 */
	ata_msleep(link->ap, 1);

	/* bring link back */
	rc = sata_link_resume(link, timing, deadline);
	if (rc)
		goto out;
	/* if link is offline nothing more to do */
	if (ata_phys_link_offline(link))
		goto out;

	/* Link is online.  From this point, -ENODEV too is an error. */
	if (online)
		*online = true;

	if (sata_pmp_supported(link->ap) && ata_is_host_link(link)) {
		/* If PMP is supported, we have to do follow-up SRST.
		 * Some PMPs don't send D2H Reg FIS after hardreset if
		 * the first port is empty.  Wait only for
		 * ATA_TMOUT_PMP_SRST_WAIT.
		 */
		if (check_ready) {
			unsigned long pmp_deadline;

			pmp_deadline = ata_deadline(jiffies,
						    ATA_TMOUT_PMP_SRST_WAIT);
			if (time_after(pmp_deadline, deadline))
				pmp_deadline = deadline;
			ata_wait_ready(link, pmp_deadline, check_ready);
		}
		rc = -EAGAIN;
		goto out;
	}

	rc = 0;
	if (check_ready)
		rc = ata_wait_ready(link, deadline, check_ready);
 out:
	if (rc && rc != -EAGAIN) {
		/* online is set iff link is online && reset succeeded */
		if (online)
			*online = false;
		ata_link_printk(link, KERN_ERR,
				"COMRESET failed (errno=%d)\n", rc);
	}
	DPRINTK("EXIT, rc=%d\n", rc);
	return rc;
}