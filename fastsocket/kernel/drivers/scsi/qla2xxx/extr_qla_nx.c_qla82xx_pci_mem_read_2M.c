#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int u64 ;
struct qla_hw_data {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_CTL_CHECK ; 
 int MIU_TA_CTL_BUSY ; 
 int MIU_TA_CTL_ENABLE ; 
 int MIU_TA_CTL_START ; 
 int MIU_TEST_AGT_ADDR_HI ; 
 int MIU_TEST_AGT_ADDR_LO ; 
 int MIU_TEST_AGT_CTRL ; 
 int MIU_TEST_AGT_RDDATA (int) ; 
 int QLA82XX_ADDR_QDR_NET ; 
 int QLA82XX_CRB_DDR_NET ; 
 int QLA82XX_CRB_QDR_NET ; 
 int QLA82XX_P3_ADDR_QDR_NET_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ printk_ratelimit () ; 
 scalar_t__ qla82xx_pci_mem_bound_check (struct qla_hw_data*,int,int) ; 
 int qla82xx_pci_mem_read_direct (struct qla_hw_data*,int,void*,int) ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int,int) ; 

__attribute__((used)) static int
qla82xx_pci_mem_read_2M(struct qla_hw_data *ha,
		u64 off, void *data, int size)
{
	int i, j = 0, k, start, end, loop, sz[2], off0[2];
	int	      shift_amount;
	uint32_t      temp;
	uint64_t      off8, val, mem_crb, word[2] = {0, 0};

	/*
	 * If not MN, go check for MS or invalid.
	 */

	if (off >= QLA82XX_ADDR_QDR_NET && off <= QLA82XX_P3_ADDR_QDR_NET_MAX)
		mem_crb = QLA82XX_CRB_QDR_NET;
	else {
		mem_crb = QLA82XX_CRB_DDR_NET;
		if (qla82xx_pci_mem_bound_check(ha, off, size) == 0)
			return qla82xx_pci_mem_read_direct(ha,
			    off, data, size);
	}

	off8 = off & 0xfffffff0;
	off0[0] = off & 0xf;
	sz[0] = (size < (16 - off0[0])) ? size : (16 - off0[0]);
	shift_amount = 4;
	loop = ((off0[0] + size - 1) >> shift_amount) + 1;
	off0[1] = 0;
	sz[1] = size - sz[0];

	for (i = 0; i < loop; i++) {
		temp = off8 + (i << shift_amount);
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_ADDR_LO, temp);
		temp = 0;
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_ADDR_HI, temp);
		temp = MIU_TA_CTL_ENABLE;
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_CTRL, temp);
		temp = MIU_TA_CTL_START | MIU_TA_CTL_ENABLE;
		qla82xx_wr_32(ha, mem_crb + MIU_TEST_AGT_CTRL, temp);

		for (j = 0; j < MAX_CTL_CHECK; j++) {
			temp = qla82xx_rd_32(ha, mem_crb + MIU_TEST_AGT_CTRL);
			if ((temp & MIU_TA_CTL_BUSY) == 0)
				break;
		}

		if (j >= MAX_CTL_CHECK) {
			if (printk_ratelimit())
				dev_err(&ha->pdev->dev,
				    "failed to read through agent\n");
			break;
		}

		start = off0[i] >> 2;
		end   = (off0[i] + sz[i] - 1) >> 2;
		for (k = start; k <= end; k++) {
			temp = qla82xx_rd_32(ha,
					mem_crb + MIU_TEST_AGT_RDDATA(k));
			word[i] |= ((uint64_t)temp << (32 * (k & 1)));
		}
	}

	if (j >= MAX_CTL_CHECK)
		return -1;

	if ((off0[0] & 7) == 0) {
		val = word[0];
	} else {
		val = ((word[0] >> (off0[0] * 8)) & (~(~0ULL << (sz[0] * 8)))) |
			((word[1] & (~(~0ULL << (sz[1] * 8)))) << (sz[0] * 8));
	}

	switch (size) {
	case 1:
		*(uint8_t  *)data = val;
		break;
	case 2:
		*(uint16_t *)data = val;
		break;
	case 4:
		*(uint32_t *)data = val;
		break;
	case 8:
		*(uint64_t *)data = val;
		break;
	}
	return 0;
}