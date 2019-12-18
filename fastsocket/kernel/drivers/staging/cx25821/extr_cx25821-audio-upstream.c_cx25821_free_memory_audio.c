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
struct cx25821_dev {int /*<<< orphan*/ * _audiodata_buf_virt_addr; int /*<<< orphan*/  _audiodata_buf_phys_addr; int /*<<< orphan*/  _audiodata_buf_size; int /*<<< orphan*/  pci; int /*<<< orphan*/ * _risc_virt_addr; int /*<<< orphan*/  _risc_phys_addr; int /*<<< orphan*/  _audiorisc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cx25821_free_memory_audio(struct cx25821_dev *dev)
{
	if (dev->_risc_virt_addr) {
		pci_free_consistent(dev->pci, dev->_audiorisc_size,
				    dev->_risc_virt_addr, dev->_risc_phys_addr);
		dev->_risc_virt_addr = NULL;
	}

	if (dev->_audiodata_buf_virt_addr) {
		pci_free_consistent(dev->pci, dev->_audiodata_buf_size,
				    dev->_audiodata_buf_virt_addr,
				    dev->_audiodata_buf_phys_addr);
		dev->_audiodata_buf_virt_addr = NULL;
	}
}