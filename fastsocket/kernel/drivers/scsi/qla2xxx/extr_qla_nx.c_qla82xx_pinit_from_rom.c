#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int dummy; } ;
struct crb_addr_pair {int addr; int data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ISP_ACTIVE ; 
 unsigned long ADDR_ERROR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCIE_SETUP_FUNCTION ; 
 int /*<<< orphan*/  PCIE_SETUP_FUNCTION2 ; 
 unsigned long QLA82XX_CAM_RAM (int) ; 
 unsigned long QLA82XX_CRB_DDR_NET ; 
 int QLA82XX_CRB_EPG ; 
 int QLA82XX_CRB_I2Q ; 
 int QLA82XX_CRB_NIU ; 
 int QLA82XX_CRB_PEG_NET_0 ; 
 int QLA82XX_CRB_PEG_NET_1 ; 
 int QLA82XX_CRB_PEG_NET_2 ; 
 int QLA82XX_CRB_PEG_NET_3 ; 
 int QLA82XX_CRB_PEG_NET_4 ; 
 int QLA82XX_CRB_PEG_NET_D ; 
 int QLA82XX_CRB_PEG_NET_I ; 
 unsigned long QLA82XX_CRB_SMB ; 
 int QLA82XX_CRB_SRE ; 
 int QLA82XX_CRB_TIMER ; 
 unsigned long QLA82XX_PCIE_REG (int /*<<< orphan*/ ) ; 
 unsigned long QLA82XX_PCI_CRBSPACE ; 
 unsigned long QLA82XX_ROMUSB_GLB_SW_RESET ; 
 int ROMUSB_GLB ; 
 int /*<<< orphan*/  kfree (struct crb_addr_pair*) ; 
 struct crb_addr_pair* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 unsigned long qla82xx_decode_crb_addr (unsigned long) ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int) ; 
 scalar_t__ qla82xx_rom_fast_read (struct qla_hw_data*,int,...) ; 
 int /*<<< orphan*/  qla82xx_rom_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_rom_unlock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla82xx_pinit_from_rom(scsi_qla_host_t *vha)
{
	int addr, val;
	int i ;
	struct crb_addr_pair *buf;
	unsigned long off;
	unsigned offset, n;
	struct qla_hw_data *ha = vha->hw;

	/* Halt all the individual PEGs and other blocks of the ISP */
	qla82xx_rom_lock(ha);

	/* disable all I2Q */
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x10, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x14, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x18, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x1c, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x20, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_I2Q + 0x24, 0x0);

	/* disable all niu interrupts */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x40, 0xff);
	/* disable xge rx/tx */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x70000, 0x00);
	/* disable xg1 rx/tx */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x80000, 0x00);
	/* disable sideband mac */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x90000, 0x00);
	/* disable ap0 mac */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0xa0000, 0x00);
	/* disable ap1 mac */
	qla82xx_wr_32(ha, QLA82XX_CRB_NIU + 0xb0000, 0x00);

	/* halt sre */
	val = qla82xx_rd_32(ha, QLA82XX_CRB_SRE + 0x1000);
	qla82xx_wr_32(ha, QLA82XX_CRB_SRE + 0x1000, val & (~(0x1)));

	/* halt epg */
	qla82xx_wr_32(ha, QLA82XX_CRB_EPG + 0x1300, 0x1);

	/* halt timers */
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x0, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x8, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x10, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x18, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x100, 0x0);
	qla82xx_wr_32(ha, QLA82XX_CRB_TIMER + 0x200, 0x0);

	/* halt pegs */
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0 + 0x3c, 1);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_1 + 0x3c, 1);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_2 + 0x3c, 1);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_3 + 0x3c, 1);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_4 + 0x3c, 1);
	msleep(5);

	/* big hammer */
	if (test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags))
		/* don't reset CAM block on reset */
		qla82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, 0xfeffffff);
	else
		qla82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, 0xffffffff);
	qla82xx_rom_unlock(ha);

	/* Read the signature value from the flash.
	 * Offset 0: Contain signature (0xcafecafe)
	 * Offset 4: Offset and number of addr/value pairs
	 * that present in CRB initialize sequence
	 */
	if (qla82xx_rom_fast_read(ha, 0, &n) != 0 || n != 0xcafecafeUL ||
	    qla82xx_rom_fast_read(ha, 4, &n) != 0) {
		ql_log(ql_log_fatal, vha, 0x006e,
		    "Error Reading crb_init area: n: %08x.\n", n);
		return -1;
	}

	/* Offset in flash = lower 16 bits
	 * Number of enteries = upper 16 bits
	 */
	offset = n & 0xffffU;
	n = (n >> 16) & 0xffffU;

	/* number of addr/value pair should not exceed 1024 entries */
	if (n  >= 1024) {
		ql_log(ql_log_fatal, vha, 0x0071,
		    "Card flash not initialized:n=0x%x.\n", n);
		return -1;
	}

	ql_log(ql_log_info, vha, 0x0072,
	    "%d CRB init values found in ROM.\n", n);

	buf = kmalloc(n * sizeof(struct crb_addr_pair), GFP_KERNEL);
	if (buf == NULL) {
		ql_log(ql_log_fatal, vha, 0x010c,
		    "Unable to allocate memory.\n");
		return -1;
	}

	for (i = 0; i < n; i++) {
		if (qla82xx_rom_fast_read(ha, 8*i + 4*offset, &val) != 0 ||
		    qla82xx_rom_fast_read(ha, 8*i + 4*offset + 4, &addr) != 0) {
			kfree(buf);
			return -1;
		}

		buf[i].addr = addr;
		buf[i].data = val;
	}

	for (i = 0; i < n; i++) {
		/* Translate internal CRB initialization
		 * address to PCI bus address
		 */
		off = qla82xx_decode_crb_addr((unsigned long)buf[i].addr) +
		    QLA82XX_PCI_CRBSPACE;
		/* Not all CRB  addr/value pair to be written,
		 * some of them are skipped
		 */

		/* skipping cold reboot MAGIC */
		if (off == QLA82XX_CAM_RAM(0x1fc))
			continue;

		/* do not reset PCI */
		if (off == (ROMUSB_GLB + 0xbc))
			continue;

		/* skip core clock, so that firmware can increase the clock */
		if (off == (ROMUSB_GLB + 0xc8))
			continue;

		/* skip the function enable register */
		if (off == QLA82XX_PCIE_REG(PCIE_SETUP_FUNCTION))
			continue;

		if (off == QLA82XX_PCIE_REG(PCIE_SETUP_FUNCTION2))
			continue;

		if ((off & 0x0ff00000) == QLA82XX_CRB_SMB)
			continue;

		if ((off & 0x0ff00000) == QLA82XX_CRB_DDR_NET)
			continue;

		if (off == ADDR_ERROR) {
			ql_log(ql_log_fatal, vha, 0x0116,
			    "Unknow addr: 0x%08lx.\n", buf[i].addr);
			continue;
		}

		qla82xx_wr_32(ha, off, buf[i].data);

		/* ISP requires much bigger delay to settle down,
		 * else crb_window returns 0xffffffff
		 */
		if (off == QLA82XX_ROMUSB_GLB_SW_RESET)
			msleep(1000);

		/* ISP requires millisec delay between
		 * successive CRB register updates
		 */
		msleep(1);
	}

	kfree(buf);

	/* Resetting the data and instruction cache */
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_D+0xec, 0x1e);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_D+0x4c, 8);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_I+0x4c, 8);

	/* Clear all protocol processing engines */
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0+0x8, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0+0xc, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_1+0x8, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_1+0xc, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_2+0x8, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_2+0xc, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_3+0x8, 0);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_3+0xc, 0);
	return 0;
}