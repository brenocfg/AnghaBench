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
typedef  int uint16_t ;
struct qla_hw_data {int max_req_queues; int max_rsp_queues; int msix_count; int /*<<< orphan*/  pdev; void* msixbase; void* mqiobase; void* iobase; int /*<<< orphan*/  bars; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IORESOURCE_MEM ; 
 scalar_t__ MIN_IOBASE_LEN ; 
 int /*<<< orphan*/  QLA2XXX_DRIVER_NAME ; 
 int /*<<< orphan*/  QLA_83XX_PCI_MSIX_CONTROL ; 
 int QLA_MQ_SIZE ; 
 void* ioremap (int /*<<< orphan*/ ,scalar_t__) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_request_selected_regions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int ql2xmaxqueues ; 
 scalar_t__ ql2xmultique_tag ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_dbg_multiq ; 
 int /*<<< orphan*/  ql_dbg_pci (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_pci (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 

__attribute__((used)) static int
qla83xx_iospace_config(struct qla_hw_data *ha)
{
	uint16_t msix;
	int cpus;

	if (pci_request_selected_regions(ha->pdev, ha->bars,
	    QLA2XXX_DRIVER_NAME)) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0117,
		    "Failed to reserve PIO/MMIO regions (%s), aborting.\n",
		    pci_name(ha->pdev));

		goto iospace_error_exit;
	}

	/* Use MMIO operations for all accesses. */
	if (!(pci_resource_flags(ha->pdev, 0) & IORESOURCE_MEM)) {
		ql_log_pci(ql_log_warn, ha->pdev, 0x0118,
		    "Invalid pci I/O region size (%s).\n",
		    pci_name(ha->pdev));
		goto iospace_error_exit;
	}
	if (pci_resource_len(ha->pdev, 0) < MIN_IOBASE_LEN) {
		ql_log_pci(ql_log_warn, ha->pdev, 0x0119,
		    "Invalid PCI mem region size (%s), aborting\n",
			pci_name(ha->pdev));
		goto iospace_error_exit;
	}

	ha->iobase = ioremap(pci_resource_start(ha->pdev, 0), MIN_IOBASE_LEN);
	if (!ha->iobase) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x011a,
		    "Cannot remap MMIO (%s), aborting.\n",
		    pci_name(ha->pdev));
		goto iospace_error_exit;
	}

	/* 64bit PCI BAR - BAR2 will correspoond to region 4 */
	/* 83XX 26XX always use MQ type access for queues - mbar 2, a.k.a region 4 */
	ha->max_req_queues = ha->max_rsp_queues = 1;
	ha->mqiobase = ioremap(pci_resource_start(ha->pdev, 4),
			pci_resource_len(ha->pdev, 4));

	if (!ha->mqiobase) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x011d,
		    "BAR2/region4 not enabled\n");
		goto mqiobase_exit;
	}

	ha->msixbase = ioremap(pci_resource_start(ha->pdev, 2),
			pci_resource_len(ha->pdev, 2));
	if (ha->msixbase) {
		/* Read MSIX vector size of the board */
		pci_read_config_word(ha->pdev, QLA_83XX_PCI_MSIX_CONTROL, &msix);
		ha->msix_count = msix;
		/* Max queues are bounded by available msix vectors */
		/* queue 0 uses two msix vectors */
		if (ql2xmultique_tag) {
			cpus = num_online_cpus();
			ha->max_rsp_queues = (ha->msix_count - 1 > cpus) ?
				(cpus + 1) : (ha->msix_count - 1);
			ha->max_req_queues = 2;
		} else if (ql2xmaxqueues > 1) {
			ha->max_req_queues = ql2xmaxqueues > QLA_MQ_SIZE ?
						QLA_MQ_SIZE : ql2xmaxqueues;
			ql_dbg_pci(ql_dbg_multiq, ha->pdev, 0xc00c,
			    "QoS mode set, max no of request queues:%d.\n",
			    ha->max_req_queues);
			ql_dbg_pci(ql_dbg_init, ha->pdev, 0x011b,
			    "QoS mode set, max no of request queues:%d.\n",
			    ha->max_req_queues);
		}
		ql_log_pci(ql_log_info, ha->pdev, 0x011c,
		    "MSI-X vector count: %d.\n", msix);
	} else
		ql_log_pci(ql_log_info, ha->pdev, 0x011e,
		    "BAR 1 not enabled.\n");

mqiobase_exit:
	ha->msix_count = ha->max_rsp_queues + 1;
	ql_dbg_pci(ql_dbg_init, ha->pdev, 0x011f,
	    "MSIX Count:%d.\n", ha->msix_count);
	return (0);

iospace_error_exit:
	return (-ENOMEM);
}