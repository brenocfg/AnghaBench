#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int port0; } ;
struct qla_hw_data {int port_no; int portnum; void* fw_srisc_address; TYPE_1__ flags; int /*<<< orphan*/  device_type; TYPE_2__* pdev; } ;
struct TYPE_5__ {int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_EXTENDED_IDS ; 
 int /*<<< orphan*/  DT_FWI2 ; 
 int /*<<< orphan*/  DT_IIDMA ; 
 int /*<<< orphan*/  DT_ISP2031 ; 
 int /*<<< orphan*/  DT_ISP2100 ; 
 int /*<<< orphan*/  DT_ISP2200 ; 
 int /*<<< orphan*/  DT_ISP2300 ; 
 int /*<<< orphan*/  DT_ISP2312 ; 
 int /*<<< orphan*/  DT_ISP2322 ; 
 int /*<<< orphan*/  DT_ISP2422 ; 
 int /*<<< orphan*/  DT_ISP2432 ; 
 int /*<<< orphan*/  DT_ISP2532 ; 
 int /*<<< orphan*/  DT_ISP5422 ; 
 int /*<<< orphan*/  DT_ISP5432 ; 
 int /*<<< orphan*/  DT_ISP6312 ; 
 int /*<<< orphan*/  DT_ISP6322 ; 
 int /*<<< orphan*/  DT_ISP8001 ; 
 int /*<<< orphan*/  DT_ISP8021 ; 
 int /*<<< orphan*/  DT_ISP8031 ; 
 int /*<<< orphan*/  DT_ISP8432 ; 
 int /*<<< orphan*/  DT_ISPFX00 ; 
 int /*<<< orphan*/  DT_OEM_001 ; 
 int /*<<< orphan*/  DT_T10_PI ; 
 int /*<<< orphan*/  DT_ZIO_SUPPORTED ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
#define  PCI_DEVICE_ID_QLOGIC_ISP2031 145 
#define  PCI_DEVICE_ID_QLOGIC_ISP2100 144 
#define  PCI_DEVICE_ID_QLOGIC_ISP2200 143 
#define  PCI_DEVICE_ID_QLOGIC_ISP2300 142 
#define  PCI_DEVICE_ID_QLOGIC_ISP2312 141 
#define  PCI_DEVICE_ID_QLOGIC_ISP2322 140 
#define  PCI_DEVICE_ID_QLOGIC_ISP2422 139 
#define  PCI_DEVICE_ID_QLOGIC_ISP2432 138 
#define  PCI_DEVICE_ID_QLOGIC_ISP2532 137 
#define  PCI_DEVICE_ID_QLOGIC_ISP5422 136 
#define  PCI_DEVICE_ID_QLOGIC_ISP5432 135 
#define  PCI_DEVICE_ID_QLOGIC_ISP6312 134 
#define  PCI_DEVICE_ID_QLOGIC_ISP6322 133 
#define  PCI_DEVICE_ID_QLOGIC_ISP8001 132 
#define  PCI_DEVICE_ID_QLOGIC_ISP8021 131 
#define  PCI_DEVICE_ID_QLOGIC_ISP8031 130 
#define  PCI_DEVICE_ID_QLOGIC_ISP8432 129 
#define  PCI_DEVICE_ID_QLOGIC_ISPF001 128 
 int /*<<< orphan*/  PCI_INTERRUPT_PIN ; 
 void* RISC_START_ADDRESS_2100 ; 
 void* RISC_START_ADDRESS_2300 ; 
 void* RISC_START_ADDRESS_2400 ; 
 int /*<<< orphan*/  pci_read_config_byte (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_dbg_pci (int /*<<< orphan*/ ,TYPE_2__*,int,char*,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  qla82xx_init_flags (struct qla_hw_data*) ; 

__attribute__((used)) static inline void
qla2x00_set_isp_flags(struct qla_hw_data *ha)
{
	ha->device_type = DT_EXTENDED_IDS;
	switch (ha->pdev->device) {
	case PCI_DEVICE_ID_QLOGIC_ISP2100:
		ha->device_type |= DT_ISP2100;
		ha->device_type &= ~DT_EXTENDED_IDS;
		ha->fw_srisc_address = RISC_START_ADDRESS_2100;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP2200:
		ha->device_type |= DT_ISP2200;
		ha->device_type &= ~DT_EXTENDED_IDS;
		ha->fw_srisc_address = RISC_START_ADDRESS_2100;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP2300:
		ha->device_type |= DT_ISP2300;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->fw_srisc_address = RISC_START_ADDRESS_2300;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP2312:
		ha->device_type |= DT_ISP2312;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->fw_srisc_address = RISC_START_ADDRESS_2300;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP2322:
		ha->device_type |= DT_ISP2322;
		ha->device_type |= DT_ZIO_SUPPORTED;
		if (ha->pdev->subsystem_vendor == 0x1028 &&
		    ha->pdev->subsystem_device == 0x0170)
			ha->device_type |= DT_OEM_001;
		ha->fw_srisc_address = RISC_START_ADDRESS_2300;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP6312:
		ha->device_type |= DT_ISP6312;
		ha->fw_srisc_address = RISC_START_ADDRESS_2300;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP6322:
		ha->device_type |= DT_ISP6322;
		ha->fw_srisc_address = RISC_START_ADDRESS_2300;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP2422:
		ha->device_type |= DT_ISP2422;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP2432:
		ha->device_type |= DT_ISP2432;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP8432:
		ha->device_type |= DT_ISP8432;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP5422:
		ha->device_type |= DT_ISP5422;
		ha->device_type |= DT_FWI2;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP5432:
		ha->device_type |= DT_ISP5432;
		ha->device_type |= DT_FWI2;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP2532:
		ha->device_type |= DT_ISP2532;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP8001:
		ha->device_type |= DT_ISP8001;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP8021:
		ha->device_type |= DT_ISP8021;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		/* Initialize 82XX ISP flags */
		qla82xx_init_flags(ha);
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP2031:
		ha->device_type |= DT_ISP2031;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->device_type |= DT_T10_PI;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISP8031:
		ha->device_type |= DT_ISP8031;
		ha->device_type |= DT_ZIO_SUPPORTED;
		ha->device_type |= DT_FWI2;
		ha->device_type |= DT_IIDMA;
		ha->device_type |= DT_T10_PI;
		ha->fw_srisc_address = RISC_START_ADDRESS_2400;
		break;
	case PCI_DEVICE_ID_QLOGIC_ISPF001:
		ha->device_type |= DT_ISPFX00;
		break;
	}

	if (IS_QLA82XX(ha))
		ha->port_no = !(ha->portnum & 1);
	else
		/* Get adapter physical port no from interrupt pin register. */
		pci_read_config_byte(ha->pdev, PCI_INTERRUPT_PIN, &ha->port_no);

	if (ha->port_no & 1)
		ha->flags.port0 = 1;
	else
		ha->flags.port0 = 0;
	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x000b,
	    "device_type=0x%x port=%d fw_srisc_address=0x%x.\n",
	    ha->device_type, ha->flags.port0, ha->fw_srisc_address);
}