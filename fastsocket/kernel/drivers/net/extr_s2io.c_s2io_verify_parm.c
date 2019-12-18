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
typedef  scalar_t__ u8 ;
struct pci_dev {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR_DBG ; 
 scalar_t__ INTA ; 
 int MAX_RX_BLOCKS_PER_RING ; 
 int MAX_RX_RINGS ; 
 int MAX_TX_FIFOS ; 
 scalar_t__ MSI_X ; 
 scalar_t__ NO_STEERING ; 
 scalar_t__ PCI_DEVICE_ID_HERC_UNI ; 
 scalar_t__ PCI_DEVICE_ID_HERC_WIN ; 
 int SUCCESS ; 
 scalar_t__ TX_DEFAULT_STEERING ; 
 scalar_t__ multiq ; 
 int rx_ring_mode ; 
 int rx_ring_num ; 
 int* rx_ring_sz ; 
 int tx_fifo_num ; 
 scalar_t__ tx_steering_type ; 

__attribute__((used)) static int s2io_verify_parm(struct pci_dev *pdev, u8 *dev_intr_type,
			    u8 *dev_multiq)
{
	int i;

	if ((tx_fifo_num > MAX_TX_FIFOS) || (tx_fifo_num < 1)) {
		DBG_PRINT(ERR_DBG, "Requested number of tx fifos "
			  "(%d) not supported\n", tx_fifo_num);

		if (tx_fifo_num < 1)
			tx_fifo_num = 1;
		else
			tx_fifo_num = MAX_TX_FIFOS;

		DBG_PRINT(ERR_DBG, "Default to %d tx fifos\n", tx_fifo_num);
	}

	if (multiq)
		*dev_multiq = multiq;

	if (tx_steering_type && (1 == tx_fifo_num)) {
		if (tx_steering_type != TX_DEFAULT_STEERING)
			DBG_PRINT(ERR_DBG,
				  "Tx steering is not supported with "
				  "one fifo. Disabling Tx steering.\n");
		tx_steering_type = NO_STEERING;
	}

	if ((tx_steering_type < NO_STEERING) ||
	    (tx_steering_type > TX_DEFAULT_STEERING)) {
		DBG_PRINT(ERR_DBG,
			  "Requested transmit steering not supported\n");
		DBG_PRINT(ERR_DBG, "Disabling transmit steering\n");
		tx_steering_type = NO_STEERING;
	}

	if (rx_ring_num > MAX_RX_RINGS) {
		DBG_PRINT(ERR_DBG,
			  "Requested number of rx rings not supported\n");
		DBG_PRINT(ERR_DBG, "Default to %d rx rings\n",
			  MAX_RX_RINGS);
		rx_ring_num = MAX_RX_RINGS;
	}

	if ((*dev_intr_type != INTA) && (*dev_intr_type != MSI_X)) {
		DBG_PRINT(ERR_DBG, "Wrong intr_type requested. "
			  "Defaulting to INTA\n");
		*dev_intr_type = INTA;
	}

	if ((*dev_intr_type == MSI_X) &&
	    ((pdev->device != PCI_DEVICE_ID_HERC_WIN) &&
	     (pdev->device != PCI_DEVICE_ID_HERC_UNI))) {
		DBG_PRINT(ERR_DBG, "Xframe I does not support MSI_X. "
			  "Defaulting to INTA\n");
		*dev_intr_type = INTA;
	}

	if ((rx_ring_mode != 1) && (rx_ring_mode != 2)) {
		DBG_PRINT(ERR_DBG, "Requested ring mode not supported\n");
		DBG_PRINT(ERR_DBG, "Defaulting to 1-buffer mode\n");
		rx_ring_mode = 1;
	}

	for (i = 0; i < MAX_RX_RINGS; i++)
		if (rx_ring_sz[i] > MAX_RX_BLOCKS_PER_RING) {
			DBG_PRINT(ERR_DBG, "Requested rx ring size not "
				  "supported\nDefaulting to %d\n",
				  MAX_RX_BLOCKS_PER_RING);
			rx_ring_sz[i] = MAX_RX_BLOCKS_PER_RING;
		}

	return SUCCESS;
}