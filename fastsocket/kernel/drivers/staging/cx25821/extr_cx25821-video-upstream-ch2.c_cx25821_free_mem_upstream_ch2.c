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
struct cx25821_dev {int /*<<< orphan*/ * _data_buf_virt_addr_ch2; int /*<<< orphan*/  _data_buf_phys_addr_ch2; int /*<<< orphan*/  _data_buf_size_ch2; int /*<<< orphan*/  pci; int /*<<< orphan*/ * _dma_virt_addr_ch2; int /*<<< orphan*/  _dma_phys_addr_ch2; int /*<<< orphan*/  _risc_size_ch2; scalar_t__ _is_running_ch2; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25821_stop_upstream_video_ch2 (struct cx25821_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cx25821_free_mem_upstream_ch2(struct cx25821_dev *dev)
{
	if (dev->_is_running_ch2) {
		cx25821_stop_upstream_video_ch2(dev);
	}

	if (dev->_dma_virt_addr_ch2) {
		pci_free_consistent(dev->pci, dev->_risc_size_ch2,
				    dev->_dma_virt_addr_ch2,
				    dev->_dma_phys_addr_ch2);
		dev->_dma_virt_addr_ch2 = NULL;
	}

	if (dev->_data_buf_virt_addr_ch2) {
		pci_free_consistent(dev->pci, dev->_data_buf_size_ch2,
				    dev->_data_buf_virt_addr_ch2,
				    dev->_data_buf_phys_addr_ch2);
		dev->_data_buf_virt_addr_ch2 = NULL;
	}
}