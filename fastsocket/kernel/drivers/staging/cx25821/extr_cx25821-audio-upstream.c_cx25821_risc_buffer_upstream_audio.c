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
struct pci_dev {int dummy; } ;
struct cx25821_dev {int _risc_phys_start_addr; int /*<<< orphan*/ * _risc_virt_addr; scalar_t__ _audiodata_buf_phys_addr; } ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int AUDIO_DATA_BUF_SZ ; 
 int AUDIO_RISC_DMA_BUF_SIZE ; 
 int AUDIO_SYNC_LINE ; 
 int NUM_AUDIO_FRAMES ; 
 int NUM_NO_OPS ; 
 int RISC_CNT_INC ; 
 int RISC_CNT_RESET ; 
 int RISC_IRQ1 ; 
 int RISC_JUMP ; 
 int RISC_NOOP ; 
 int RISC_RESYNC ; 
 int RISC_SYNC_INSTRUCTION_SIZE ; 
 scalar_t__ USE_RISC_NOOP_AUDIO ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/ * cx25821_risc_field_upstream_audio (struct cx25821_dev*,int /*<<< orphan*/ *,scalar_t__,unsigned int,int) ; 

int cx25821_risc_buffer_upstream_audio(struct cx25821_dev *dev,
				       struct pci_dev *pci,
				       unsigned int bpl, unsigned int lines)
{
	__le32 *rp;
	int fifo_enable = 0;
	int frame = 0, i = 0;
	int frame_size = AUDIO_DATA_BUF_SZ;
	int databuf_offset = 0;
	int risc_flag = RISC_CNT_INC;
	dma_addr_t risc_phys_jump_addr;

	/* Virtual address of Risc buffer program */
	rp = dev->_risc_virt_addr;

	/* sync instruction */
	*(rp++) = cpu_to_le32(RISC_RESYNC | AUDIO_SYNC_LINE);

	for (frame = 0; frame < NUM_AUDIO_FRAMES; frame++) {
		databuf_offset = frame_size * frame;

		if (frame == 0) {
			fifo_enable = 1;
			risc_flag = RISC_CNT_RESET;
		} else {
			fifo_enable = 0;
			risc_flag = RISC_CNT_INC;
		}

		//Calculate physical jump address
		if ((frame + 1) == NUM_AUDIO_FRAMES) {
			risc_phys_jump_addr =
			    dev->_risc_phys_start_addr +
			    RISC_SYNC_INSTRUCTION_SIZE;
		} else {
			risc_phys_jump_addr =
			    dev->_risc_phys_start_addr +
			    RISC_SYNC_INSTRUCTION_SIZE +
			    AUDIO_RISC_DMA_BUF_SIZE * (frame + 1);
		}

		rp = cx25821_risc_field_upstream_audio(dev, rp,
						       dev->
						       _audiodata_buf_phys_addr
						       + databuf_offset, bpl,
						       fifo_enable);

		if (USE_RISC_NOOP_AUDIO) {
			for (i = 0; i < NUM_NO_OPS; i++) {
				*(rp++) = cpu_to_le32(RISC_NOOP);
			}
		}

		// Loop to (Nth)FrameRISC or to Start of Risc program & generate IRQ
		*(rp++) = cpu_to_le32(RISC_JUMP | RISC_IRQ1 | risc_flag);
		*(rp++) = cpu_to_le32(risc_phys_jump_addr);
		*(rp++) = cpu_to_le32(0);

		//Recalculate virtual address based on frame index
		rp = dev->_risc_virt_addr + RISC_SYNC_INSTRUCTION_SIZE / 4 +
		    (AUDIO_RISC_DMA_BUF_SIZE * (frame + 1) / 4);
	}

	return 0;
}