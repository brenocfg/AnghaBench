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
typedef  int u32 ;
struct sram_channel {int /*<<< orphan*/  dma_ctl; int /*<<< orphan*/  int_msk; } ;
struct cx25821_dev {int /*<<< orphan*/ * _filename_ch2; int /*<<< orphan*/ * _irq_queues_ch2; int /*<<< orphan*/  _file_status_ch2; scalar_t__ _frame_count_ch2; scalar_t__ _is_first_frame_ch2; scalar_t__ _is_running_ch2; int /*<<< orphan*/  _data_buf_size_ch2; scalar_t__ _data_buf_virt_addr_ch2; struct sram_channel* sram_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_OF_FILE ; 
 int FLD_VID_FIFO_EN ; 
 int FLD_VID_RISC_EN ; 
 int /*<<< orphan*/  VID_CH_MODE_SEL ; 
 size_t VID_UPSTREAM_SRAM_CHANNEL_J ; 
 int _intr_msk ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

void cx25821_stop_upstream_video_ch2(struct cx25821_dev *dev)
{
	struct sram_channel *sram_ch =
	    &dev->sram_channels[VID_UPSTREAM_SRAM_CHANNEL_J];
	u32 tmp = 0;

	if (!dev->_is_running_ch2) {
		printk
		    ("cx25821: No video file is currently running so return!\n");
		return;
	}
	//Disable RISC interrupts
	tmp = cx_read(sram_ch->int_msk);
	cx_write(sram_ch->int_msk, tmp & ~_intr_msk);

	//Turn OFF risc and fifo
	tmp = cx_read(sram_ch->dma_ctl);
	cx_write(sram_ch->dma_ctl, tmp & ~(FLD_VID_FIFO_EN | FLD_VID_RISC_EN));

	//Clear data buffer memory
	if (dev->_data_buf_virt_addr_ch2)
		memset(dev->_data_buf_virt_addr_ch2, 0,
		       dev->_data_buf_size_ch2);

	dev->_is_running_ch2 = 0;
	dev->_is_first_frame_ch2 = 0;
	dev->_frame_count_ch2 = 0;
	dev->_file_status_ch2 = END_OF_FILE;

	if (dev->_irq_queues_ch2) {
		kfree(dev->_irq_queues_ch2);
		dev->_irq_queues_ch2 = NULL;
	}

	if (dev->_filename_ch2 != NULL)
		kfree(dev->_filename_ch2);

	tmp = cx_read(VID_CH_MODE_SEL);
	cx_write(VID_CH_MODE_SEL, tmp & 0xFFFFFE00);
}