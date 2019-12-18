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
struct scsi_qla_host {int qdr_sn_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned long long QLA82XX_P3_ADDR_QDR_NET_MAX ; 
 unsigned long long QLA8XXX_ADDR_DDR_NET ; 
 unsigned long long QLA8XXX_ADDR_DDR_NET_MAX ; 
 scalar_t__ QLA8XXX_ADDR_IN_RANGE (unsigned long long,unsigned long long,unsigned long long) ; 
 unsigned long long QLA8XXX_ADDR_OCM0 ; 
 unsigned long long QLA8XXX_ADDR_OCM0_MAX ; 
 unsigned long long QLA8XXX_ADDR_OCM1 ; 
 unsigned long long QLA8XXX_ADDR_OCM1_MAX ; 
 unsigned long long QLA8XXX_ADDR_QDR_NET ; 

__attribute__((used)) static int qla4_82xx_pci_is_same_window(struct scsi_qla_host *ha,
		unsigned long long addr)
{
	int window;
	unsigned long long qdr_max;

	qdr_max = QLA82XX_P3_ADDR_QDR_NET_MAX;

	if (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_DDR_NET,
	    QLA8XXX_ADDR_DDR_NET_MAX)) {
		/* DDR network side */
		BUG();	/* MN access can not come here */
	} else if (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_OCM0,
	     QLA8XXX_ADDR_OCM0_MAX)) {
		return 1;
	} else if (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_OCM1,
	     QLA8XXX_ADDR_OCM1_MAX)) {
		return 1;
	} else if (QLA8XXX_ADDR_IN_RANGE(addr, QLA8XXX_ADDR_QDR_NET,
	    qdr_max)) {
		/* QDR network side */
		window = ((addr - QLA8XXX_ADDR_QDR_NET) >> 22) & 0x3f;
		if (ha->qdr_sn_window == window)
			return 1;
	}

	return 0;
}