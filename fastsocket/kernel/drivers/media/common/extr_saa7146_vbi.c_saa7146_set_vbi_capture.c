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
struct saa7146_vv {scalar_t__ current_hps_sync; } ;
struct saa7146_video_dma {int pitch; int base_page; int num_line_byte; scalar_t__ prot_addr; scalar_t__ base_odd; scalar_t__ base_even; } ;
struct TYPE_4__ {int dma_handle; } ;
struct saa7146_dev {TYPE_2__ d_rps1; struct saa7146_vv* vv_data; } ;
struct saa7146_buf {TYPE_1__* pt; } ;
struct TYPE_3__ {int dma; scalar_t__ offset; } ;

/* Variables and functions */
 unsigned long CMD_E_FID_A ; 
 unsigned long CMD_E_FID_B ; 
 unsigned long CMD_INTERRUPT ; 
 unsigned long CMD_O_FID_A ; 
 unsigned long CMD_O_FID_B ; 
 unsigned long CMD_PAUSE ; 
 unsigned long CMD_STOP ; 
 int CMD_WR_REG ; 
 int CMD_WR_REG_MASK ; 
 unsigned long MASK_04 ; 
 unsigned long MASK_12 ; 
 int MASK_13 ; 
 unsigned long MASK_20 ; 
 unsigned long MASK_28 ; 
 int MASK_29 ; 
 int MC1 ; 
 int MC2 ; 
 int ME1 ; 
 int RPS_ADDR1 ; 
 scalar_t__ SAA7146_HPS_SYNC_PORT_A ; 
 int /*<<< orphan*/  SAA7146_IER_ENABLE (struct saa7146_dev*,unsigned long) ; 
 int /*<<< orphan*/  WRITE_RPS1 (unsigned long) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int,int) ; 
 int /*<<< orphan*/  saa7146_write_out_dma (struct saa7146_dev*,int,struct saa7146_video_dma*) ; 
 int vbi_pixel_to_capture ; 

__attribute__((used)) static void saa7146_set_vbi_capture(struct saa7146_dev *dev, struct saa7146_buf *buf, struct saa7146_buf *next)
{
	struct saa7146_vv *vv = dev->vv_data;

	struct saa7146_video_dma vdma3;

	int count = 0;
	unsigned long e_wait = vv->current_hps_sync == SAA7146_HPS_SYNC_PORT_A ? CMD_E_FID_A : CMD_E_FID_B;
	unsigned long o_wait = vv->current_hps_sync == SAA7146_HPS_SYNC_PORT_A ? CMD_O_FID_A : CMD_O_FID_B;

/*
	vdma3.base_even	= 0xc8000000+2560*70;
	vdma3.base_odd	= 0xc8000000;
	vdma3.prot_addr	= 0xc8000000+2560*164;
	vdma3.pitch	= 2560;
	vdma3.base_page	= 0;
	vdma3.num_line_byte = (64<<16)|((vbi_pixel_to_capture)<<0); // set above!
*/
	vdma3.base_even	= buf->pt[2].offset;
	vdma3.base_odd	= buf->pt[2].offset + 16 * vbi_pixel_to_capture;
	vdma3.prot_addr	= buf->pt[2].offset + 16 * 2 * vbi_pixel_to_capture;
	vdma3.pitch	= vbi_pixel_to_capture;
	vdma3.base_page	= buf->pt[2].dma | ME1;
	vdma3.num_line_byte = (16 << 16) | vbi_pixel_to_capture;

	saa7146_write_out_dma(dev, 3, &vdma3);

	/* write beginning of rps-program */
	count = 0;

	/* wait for o_fid_a/b / e_fid_a/b toggle only if bit 1 is not set */

	/* we don't wait here for the first field anymore. this is different from the video
	   capture and might cause that the first buffer is only half filled (with only
	   one field). but since this is some sort of streaming data, this is not that negative.
	   but by doing this, we can use the whole engine from videobuf-dma-sg.c... */

/*
	WRITE_RPS1(CMD_PAUSE | CMD_OAN | CMD_SIG1 | e_wait);
	WRITE_RPS1(CMD_PAUSE | CMD_OAN | CMD_SIG1 | o_wait);
*/
	/* set bit 1 */
	WRITE_RPS1(CMD_WR_REG | (1 << 8) | (MC2/4));
	WRITE_RPS1(MASK_28 | MASK_12);

	/* turn on video-dma3 */
	WRITE_RPS1(CMD_WR_REG_MASK | (MC1/4));
	WRITE_RPS1(MASK_04 | MASK_20);			/* => mask */
	WRITE_RPS1(MASK_04 | MASK_20);			/* => values */

	/* wait for o_fid_a/b / e_fid_a/b toggle */
	WRITE_RPS1(CMD_PAUSE | o_wait);
	WRITE_RPS1(CMD_PAUSE | e_wait);

	/* generate interrupt */
	WRITE_RPS1(CMD_INTERRUPT);

	/* stop */
	WRITE_RPS1(CMD_STOP);

	/* enable rps1 irqs */
	SAA7146_IER_ENABLE(dev, MASK_28);

	/* write the address of the rps-program */
	saa7146_write(dev, RPS_ADDR1, dev->d_rps1.dma_handle);

	/* turn on rps */
	saa7146_write(dev, MC1, (MASK_13 | MASK_29));
}