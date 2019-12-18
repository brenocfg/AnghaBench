#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {unsigned int dma_desc_phys_addr; unsigned int* dio_buffer_phys_addr; unsigned int* desc_dio_buffer; unsigned int* dio_buffer; unsigned int num_dma_descriptors; unsigned int block_size; TYPE_1__* dma_desc; } ;
struct TYPE_3__ {void* next; void* pci_start_addr; void* transfer_size; void* local_start_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINT (char*,unsigned int,...) ; 
 unsigned int DMA_BUFFER_SIZE ; 
 unsigned int FIFO_REG ; 
 unsigned int NUM_DMA_BUFFERS ; 
 unsigned int NUM_DMA_DESCRIPTORS ; 
 unsigned int PLX_DESC_IN_PCI_BIT ; 
 unsigned int PLX_INTR_TERM_COUNT ; 
 unsigned int PLX_XFER_LOCAL_TO_PCI ; 
 void* cpu_to_le32 (unsigned int) ; 
 TYPE_2__* priv (struct comedi_device*) ; 

__attribute__((used)) static int setup_dma_descriptors(struct comedi_device *dev,
				 unsigned int transfer_size)
{
	unsigned int buffer_index, buffer_offset;
	uint32_t next_bits = PLX_DESC_IN_PCI_BIT | PLX_INTR_TERM_COUNT |
	    PLX_XFER_LOCAL_TO_PCI;
	unsigned int i;

	if (transfer_size > DMA_BUFFER_SIZE)
		transfer_size = DMA_BUFFER_SIZE;
	transfer_size -= transfer_size % sizeof(uint32_t);
	if (transfer_size == 0)
		return -1;

	DEBUG_PRINT(" transfer_size %i\n", transfer_size);
	DEBUG_PRINT(" descriptors at 0x%lx\n",
		    (unsigned long)priv(dev)->dma_desc_phys_addr);

	buffer_offset = 0;
	buffer_index = 0;
	for (i = 0; i < NUM_DMA_DESCRIPTORS &&
	     buffer_index < NUM_DMA_BUFFERS; i++) {
		priv(dev)->dma_desc[i].pci_start_addr =
		    cpu_to_le32(priv(dev)->dio_buffer_phys_addr[buffer_index] +
				buffer_offset);
		priv(dev)->dma_desc[i].local_start_addr = cpu_to_le32(FIFO_REG);
		priv(dev)->dma_desc[i].transfer_size =
		    cpu_to_le32(transfer_size);
		priv(dev)->dma_desc[i].next =
		    cpu_to_le32((priv(dev)->dma_desc_phys_addr + (i +
								  1) *
				 sizeof(priv(dev)->dma_desc[0])) | next_bits);

		priv(dev)->desc_dio_buffer[i] =
		    priv(dev)->dio_buffer[buffer_index] +
		    (buffer_offset / sizeof(uint32_t));

		buffer_offset += transfer_size;
		if (transfer_size + buffer_offset > DMA_BUFFER_SIZE) {
			buffer_offset = 0;
			buffer_index++;
		}

		DEBUG_PRINT(" desc %i\n", i);
		DEBUG_PRINT(" start addr virt 0x%p, phys 0x%lx\n",
			    priv(dev)->desc_dio_buffer[i],
			    (unsigned long)priv(dev)->dma_desc[i].
			    pci_start_addr);
		DEBUG_PRINT(" next 0x%lx\n",
			    (unsigned long)priv(dev)->dma_desc[i].next);
	}
	priv(dev)->num_dma_descriptors = i;
	/*  fix last descriptor to point back to first */
	priv(dev)->dma_desc[i - 1].next =
	    cpu_to_le32(priv(dev)->dma_desc_phys_addr | next_bits);
	DEBUG_PRINT(" desc %i next fixup 0x%lx\n", i - 1,
		    (unsigned long)priv(dev)->dma_desc[i - 1].next);

	priv(dev)->block_size = transfer_size;

	return transfer_size;
}