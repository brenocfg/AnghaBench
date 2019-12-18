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
struct s3c2410_dma_chan {int load_state; unsigned long dcon; unsigned long xfer_unit; int /*<<< orphan*/ * next; int /*<<< orphan*/  addr_reg; } ;
struct s3c2410_dma_buf {int data; unsigned long size; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long S3C2410_DCON_AUTORELOAD ; 
 unsigned long S3C2410_DCON_NORELOAD ; 
 int S3C2410_DMALOAD_1LOADED ; 
 int S3C2410_DMALOAD_1LOADED_1RUNNING ; 
#define  S3C2410_DMALOAD_1RUNNING 129 
#define  S3C2410_DMALOAD_NONE 128 
 int /*<<< orphan*/  S3C2410_DMA_DCON ; 
 int /*<<< orphan*/  dma_wrreg (struct s3c2410_dma_chan*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dmawarn (char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,struct s3c2410_dma_buf*,...) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
s3c2410_dma_loadbuffer(struct s3c2410_dma_chan *chan,
		       struct s3c2410_dma_buf *buf)
{
	unsigned long reload;

	if (buf == NULL) {
		dmawarn("buffer is NULL\n");
		return -EINVAL;
	}

	pr_debug("s3c2410_chan_loadbuffer: loading buff %p (0x%08lx,0x%06x)\n",
		 buf, (unsigned long)buf->data, buf->size);

	/* check the state of the channel before we do anything */

	if (chan->load_state == S3C2410_DMALOAD_1LOADED) {
		dmawarn("load_state is S3C2410_DMALOAD_1LOADED\n");
	}

	if (chan->load_state == S3C2410_DMALOAD_1LOADED_1RUNNING) {
		dmawarn("state is S3C2410_DMALOAD_1LOADED_1RUNNING\n");
	}

	/* it would seem sensible if we are the last buffer to not bother
	 * with the auto-reload bit, so that the DMA engine will not try
	 * and load another transfer after this one has finished...
	 */
	if (chan->load_state == S3C2410_DMALOAD_NONE) {
		pr_debug("load_state is none, checking for noreload (next=%p)\n",
			 buf->next);
		reload = (buf->next == NULL) ? S3C2410_DCON_NORELOAD : 0;
	} else {
		//pr_debug("load_state is %d => autoreload\n", chan->load_state);
		reload = S3C2410_DCON_AUTORELOAD;
	}

	if ((buf->data & 0xf0000000) != 0x30000000) {
		dmawarn("dmaload: buffer is %p\n", (void *)buf->data);
	}

	writel(buf->data, chan->addr_reg);

	dma_wrreg(chan, S3C2410_DMA_DCON,
		  chan->dcon | reload | (buf->size/chan->xfer_unit));

	chan->next = buf->next;

	/* update the state of the channel */

	switch (chan->load_state) {
	case S3C2410_DMALOAD_NONE:
		chan->load_state = S3C2410_DMALOAD_1LOADED;
		break;

	case S3C2410_DMALOAD_1RUNNING:
		chan->load_state = S3C2410_DMALOAD_1LOADED_1RUNNING;
		break;

	default:
		dmawarn("dmaload: unknown state %d in loadbuffer\n",
			chan->load_state);
		break;
	}

	return 0;
}