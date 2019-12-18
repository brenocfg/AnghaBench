#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {unsigned long** generic_buffer_virt; int /*<<< orphan*/ ** sense_buffer_virt; int /*<<< orphan*/ * sense_buffer_phys; int /*<<< orphan*/ * generic_buffer_phys; int /*<<< orphan*/ ** command_packet_virt; int /*<<< orphan*/ * command_packet_phys; int /*<<< orphan*/  host; int /*<<< orphan*/  tw_pci_dev; } ;
typedef  TYPE_1__ TW_Device_Extension ;
typedef  int /*<<< orphan*/  TW_Command_Full ;
typedef  int /*<<< orphan*/  TW_Command_Apache_Header ;

/* Variables and functions */
 int /*<<< orphan*/  TW_DRIVER ; 
 int /*<<< orphan*/  TW_PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int TW_Q_LENGTH ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 
 unsigned long* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int twl_allocate_memory(TW_Device_Extension *tw_dev, int size, int which)
{
	int i;
	dma_addr_t dma_handle;
	unsigned long *cpu_addr;
	int retval = 1;

	cpu_addr = pci_alloc_consistent(tw_dev->tw_pci_dev, size*TW_Q_LENGTH, &dma_handle);
	if (!cpu_addr) {
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0x5, "Memory allocation failed");
		goto out;
	}

	memset(cpu_addr, 0, size*TW_Q_LENGTH);

	for (i = 0; i < TW_Q_LENGTH; i++) {
		switch(which) {
		case 0:
			tw_dev->command_packet_phys[i] = dma_handle+(i*size);
			tw_dev->command_packet_virt[i] = (TW_Command_Full *)((unsigned char *)cpu_addr + (i*size));
			break;
		case 1:
			tw_dev->generic_buffer_phys[i] = dma_handle+(i*size);
			tw_dev->generic_buffer_virt[i] = (unsigned long *)((unsigned char *)cpu_addr + (i*size));
			break;
		case 2:
			tw_dev->sense_buffer_phys[i] = dma_handle+(i*size);
			tw_dev->sense_buffer_virt[i] = (TW_Command_Apache_Header *)((unsigned char *)cpu_addr + (i*size));
			break;
		}
	}
	retval = 0;
out:
	return retval;
}