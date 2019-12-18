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
struct cx25821_dev {int /*<<< orphan*/ * _data_buf_virt_addr; int /*<<< orphan*/  _data_buf_phys_addr; int /*<<< orphan*/  _data_buf_size; int /*<<< orphan*/  pci; int /*<<< orphan*/ * _dma_virt_addr; int /*<<< orphan*/  _dma_phys_addr; int /*<<< orphan*/  _risc_size; scalar_t__ _is_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25821_stop_upstream_video_ch1 (struct cx25821_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cx25821_free_mem_upstream_ch1(struct cx25821_dev *dev)
{
	if (dev->_is_running) {
		cx25821_stop_upstream_video_ch1(dev);
	}

	if (dev->_dma_virt_addr) {
		pci_free_consistent(dev->pci, dev->_risc_size,
				    dev->_dma_virt_addr, dev->_dma_phys_addr);
		dev->_dma_virt_addr = NULL;
	}

	if (dev->_data_buf_virt_addr) {
		pci_free_consistent(dev->pci, dev->_data_buf_size,
				    dev->_data_buf_virt_addr,
				    dev->_data_buf_phys_addr);
		dev->_data_buf_virt_addr = NULL;
	}
}