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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ protocol; int device; int flags; int hob_nsect; int hob_lbal; int hob_lbam; int hob_lbah; int nsect; int lbal; int lbam; int lbah; int command; } ;
struct ata_queued_cmd {TYPE_1__ tf; TYPE_2__* ap; } ;
struct adma_port_priv {int* pkt; int /*<<< orphan*/  pkt_dma; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {struct adma_port_priv* private_data; } ;

/* Variables and functions */
 int ADMA_REGS_COMMAND ; 
 int ADMA_REGS_CONTROL ; 
 int ADMA_REGS_DEVICE ; 
 int ADMA_REGS_LBA_HIGH ; 
 int ADMA_REGS_LBA_LOW ; 
 int ADMA_REGS_LBA_MID ; 
 int ADMA_REGS_SECTOR_COUNT ; 
 scalar_t__ ATA_PROT_DMA ; 
 int ATA_TFLAG_LBA48 ; 
 int /*<<< orphan*/  VPRINTK (char*) ; 
 int /*<<< orphan*/  adma_enter_reg_mode (TYPE_2__*) ; 
 int adma_fill_sg (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  ata_sff_qc_prep (struct ata_queued_cmd*) ; 
 int cDAT ; 
 int cIEN ; 
 int cVLD ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 int rEND ; 
 int rIGN ; 
 scalar_t__ sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void adma_qc_prep(struct ata_queued_cmd *qc)
{
	struct adma_port_priv *pp = qc->ap->private_data;
	u8  *buf = pp->pkt;
	u32 pkt_dma = (u32)pp->pkt_dma;
	int i = 0;

	VPRINTK("ENTER\n");

	adma_enter_reg_mode(qc->ap);
	if (qc->tf.protocol != ATA_PROT_DMA) {
		ata_sff_qc_prep(qc);
		return;
	}

	buf[i++] = 0;	/* Response flags */
	buf[i++] = 0;	/* reserved */
	buf[i++] = cVLD | cDAT | cIEN;
	i++;		/* cLEN, gets filled in below */

	*(__le32 *)(buf+i) = cpu_to_le32(pkt_dma);	/* cNCPB */
	i += 4;		/* cNCPB */
	i += 4;		/* cPRD, gets filled in below */

	buf[i++] = 0;	/* reserved */
	buf[i++] = 0;	/* reserved */
	buf[i++] = 0;	/* reserved */
	buf[i++] = 0;	/* reserved */

	/* ATA registers; must be a multiple of 4 */
	buf[i++] = qc->tf.device;
	buf[i++] = ADMA_REGS_DEVICE;
	if ((qc->tf.flags & ATA_TFLAG_LBA48)) {
		buf[i++] = qc->tf.hob_nsect;
		buf[i++] = ADMA_REGS_SECTOR_COUNT;
		buf[i++] = qc->tf.hob_lbal;
		buf[i++] = ADMA_REGS_LBA_LOW;
		buf[i++] = qc->tf.hob_lbam;
		buf[i++] = ADMA_REGS_LBA_MID;
		buf[i++] = qc->tf.hob_lbah;
		buf[i++] = ADMA_REGS_LBA_HIGH;
	}
	buf[i++] = qc->tf.nsect;
	buf[i++] = ADMA_REGS_SECTOR_COUNT;
	buf[i++] = qc->tf.lbal;
	buf[i++] = ADMA_REGS_LBA_LOW;
	buf[i++] = qc->tf.lbam;
	buf[i++] = ADMA_REGS_LBA_MID;
	buf[i++] = qc->tf.lbah;
	buf[i++] = ADMA_REGS_LBA_HIGH;
	buf[i++] = 0;
	buf[i++] = ADMA_REGS_CONTROL;
	buf[i++] = rIGN;
	buf[i++] = 0;
	buf[i++] = qc->tf.command;
	buf[i++] = ADMA_REGS_COMMAND | rEND;

	buf[3] = (i >> 3) - 2;				/* cLEN */
	*(__le32 *)(buf+8) = cpu_to_le32(pkt_dma + i);	/* cPRD */

	i = adma_fill_sg(qc);
	wmb();	/* flush PRDs and pkt to memory */
#if 0
	/* dump out CPB + PRDs for debug */
	{
		int j, len = 0;
		static char obuf[2048];
		for (j = 0; j < i; ++j) {
			len += sprintf(obuf+len, "%02x ", buf[j]);
			if ((j & 7) == 7) {
				printk("%s\n", obuf);
				len = 0;
			}
		}
		if (len)
			printk("%s\n", obuf);
	}
#endif
}