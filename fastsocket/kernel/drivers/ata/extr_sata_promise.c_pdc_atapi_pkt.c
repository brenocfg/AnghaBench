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
struct pdc_port_priv {int* pkt; } ;
struct TYPE_4__ {int protocol; int flags; unsigned int device; int nsect; int lbal; int lbam; int lbah; int command; } ;
struct ata_queued_cmd {int* cdb; TYPE_2__ tf; TYPE_1__* dev; struct ata_port* ap; } ;
struct ata_port {int /*<<< orphan*/  link; struct pdc_port_priv* private_data; int /*<<< orphan*/  prd_dma; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  scalar_t__ __le32 ;
struct TYPE_3__ {unsigned int cdb_len; } ;

/* Variables and functions */
#define  ATAPI_PROT_DMA 129 
#define  ATAPI_PROT_NODATA 128 
 int ATA_REG_BYTEH ; 
 int ATA_REG_BYTEL ; 
 int ATA_REG_CMD ; 
 unsigned int ATA_REG_DATA ; 
 int ATA_REG_DEVICE ; 
 int ATA_REG_FEATURE ; 
 int ATA_REG_LBAL ; 
 int ATA_REG_NSECT ; 
 int ATA_TFLAG_WRITE ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (unsigned int) ; 
 unsigned int PDC_DEVICE_SATA ; 
 unsigned int PDC_FEATURE_ATAPI_DMA ; 
 unsigned int PDC_FEATURE_ATAPI_PIO ; 
 unsigned int PDC_LAST_REG ; 
 int PDC_PKT_CLEAR_BSY ; 
 int /*<<< orphan*/  PDC_PKT_NODATA ; 
 int /*<<< orphan*/  PDC_PKT_READ ; 
 int PDC_PKT_WAIT_DRDY ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,unsigned int) ; 
 scalar_t__ sata_scr_valid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdc_atapi_pkt(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	dma_addr_t sg_table = ap->prd_dma;
	unsigned int cdb_len = qc->dev->cdb_len;
	u8 *cdb = qc->cdb;
	struct pdc_port_priv *pp = ap->private_data;
	u8 *buf = pp->pkt;
	__le32 *buf32 = (__le32 *) buf;
	unsigned int dev_sel, feature;

	/* set control bits (byte 0), zero delay seq id (byte 3),
	 * and seq id (byte 2)
	 */
	switch (qc->tf.protocol) {
	case ATAPI_PROT_DMA:
		if (!(qc->tf.flags & ATA_TFLAG_WRITE))
			buf32[0] = cpu_to_le32(PDC_PKT_READ);
		else
			buf32[0] = 0;
		break;
	case ATAPI_PROT_NODATA:
		buf32[0] = cpu_to_le32(PDC_PKT_NODATA);
		break;
	default:
		BUG();
		break;
	}
	buf32[1] = cpu_to_le32(sg_table);	/* S/G table addr */
	buf32[2] = 0;				/* no next-packet */

	/* select drive */
	if (sata_scr_valid(&ap->link))
		dev_sel = PDC_DEVICE_SATA;
	else
		dev_sel = qc->tf.device;

	buf[12] = (1 << 5) | ATA_REG_DEVICE;
	buf[13] = dev_sel;
	buf[14] = (1 << 5) | ATA_REG_DEVICE | PDC_PKT_CLEAR_BSY;
	buf[15] = dev_sel; /* once more, waiting for BSY to clear */

	buf[16] = (1 << 5) | ATA_REG_NSECT;
	buf[17] = qc->tf.nsect;
	buf[18] = (1 << 5) | ATA_REG_LBAL;
	buf[19] = qc->tf.lbal;

	/* set feature and byte counter registers */
	if (qc->tf.protocol != ATAPI_PROT_DMA)
		feature = PDC_FEATURE_ATAPI_PIO;
	else
		feature = PDC_FEATURE_ATAPI_DMA;

	buf[20] = (1 << 5) | ATA_REG_FEATURE;
	buf[21] = feature;
	buf[22] = (1 << 5) | ATA_REG_BYTEL;
	buf[23] = qc->tf.lbam;
	buf[24] = (1 << 5) | ATA_REG_BYTEH;
	buf[25] = qc->tf.lbah;

	/* send ATAPI packet command 0xA0 */
	buf[26] = (1 << 5) | ATA_REG_CMD;
	buf[27] = qc->tf.command;

	/* select drive and check DRQ */
	buf[28] = (1 << 5) | ATA_REG_DEVICE | PDC_PKT_WAIT_DRDY;
	buf[29] = dev_sel;

	/* we can represent cdb lengths 2/4/6/8/10/12/14/16 */
	BUG_ON(cdb_len & ~0x1E);

	/* append the CDB as the final part */
	buf[30] = (((cdb_len >> 1) & 7) << 5) | ATA_REG_DATA | PDC_LAST_REG;
	memcpy(buf+31, cdb, cdb_len);
}