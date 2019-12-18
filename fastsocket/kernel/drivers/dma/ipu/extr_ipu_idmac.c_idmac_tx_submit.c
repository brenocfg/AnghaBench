#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ipu {int dummy; } ;
struct idmac_video_param {int /*<<< orphan*/  out_stride; int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  out_pixel_fmt; } ;
struct idmac_tx_desc {int /*<<< orphan*/  list; int /*<<< orphan*/ * sg; } ;
struct TYPE_7__ {scalar_t__ cookie; TYPE_1__* dev; } ;
struct TYPE_6__ {struct idmac_video_param video; } ;
struct idmac_channel {scalar_t__ status; int /*<<< orphan*/  chan_mutex; TYPE_3__ dma_chan; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; scalar_t__* sg; TYPE_2__ params; } ;
struct idmac {int dummy; } ;
struct dma_async_tx_descriptor {scalar_t__ cookie; TYPE_4__* chan; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_cookie_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {struct device device; } ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ IPU_CHANNEL_ENABLED ; 
 scalar_t__ IPU_CHANNEL_READY ; 
 int /*<<< orphan*/  IPU_ROTATE_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  async_tx_clear_ack (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dump_idmac_reg (struct ipu*) ; 
 int ipu_enable_channel (struct idmac*,struct idmac_channel*) ; 
 scalar_t__ ipu_init_channel_buffer (struct idmac_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipu_submit_channel_buffers (struct idmac_channel*,struct idmac_tx_desc*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 
 scalar_t__ sg_is_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct idmac* to_idmac (int /*<<< orphan*/ ) ; 
 struct idmac_channel* to_idmac_chan (TYPE_4__*) ; 
 struct ipu* to_ipu (struct idmac*) ; 
 struct idmac_tx_desc* to_tx_desc (struct dma_async_tx_descriptor*) ; 

__attribute__((used)) static dma_cookie_t idmac_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct idmac_tx_desc *desc = to_tx_desc(tx);
	struct idmac_channel *ichan = to_idmac_chan(tx->chan);
	struct idmac *idmac = to_idmac(tx->chan->device);
	struct ipu *ipu = to_ipu(idmac);
	struct device *dev = &ichan->dma_chan.dev->device;
	dma_cookie_t cookie;
	unsigned long flags;
	int ret;

	/* Sanity check */
	if (!list_empty(&desc->list)) {
		/* The descriptor doesn't belong to client */
		dev_err(dev, "Descriptor %p not prepared!\n", tx);
		return -EBUSY;
	}

	mutex_lock(&ichan->chan_mutex);

	async_tx_clear_ack(tx);

	if (ichan->status < IPU_CHANNEL_READY) {
		struct idmac_video_param *video = &ichan->params.video;
		/*
		 * Initial buffer assignment - the first two sg-entries from
		 * the descriptor will end up in the IDMAC buffers
		 */
		dma_addr_t dma_1 = sg_is_last(desc->sg) ? 0 :
			sg_dma_address(&desc->sg[1]);

		WARN_ON(ichan->sg[0] || ichan->sg[1]);

		cookie = ipu_init_channel_buffer(ichan,
						 video->out_pixel_fmt,
						 video->out_width,
						 video->out_height,
						 video->out_stride,
						 IPU_ROTATE_NONE,
						 sg_dma_address(&desc->sg[0]),
						 dma_1);
		if (cookie < 0)
			goto out;
	}

	dev_dbg(dev, "Submitting sg %p\n", &desc->sg[0]);

	cookie = ichan->dma_chan.cookie;

	if (++cookie < 0)
		cookie = 1;

	/* from dmaengine.h: "last cookie value returned to client" */
	ichan->dma_chan.cookie = cookie;
	tx->cookie = cookie;

	/* ipu->lock can be taken under ichan->lock, but not v.v. */
	spin_lock_irqsave(&ichan->lock, flags);

	list_add_tail(&desc->list, &ichan->queue);
	/* submit_buffers() atomically verifies and fills empty sg slots */
	ret = ipu_submit_channel_buffers(ichan, desc);

	spin_unlock_irqrestore(&ichan->lock, flags);

	if (ret < 0) {
		cookie = ret;
		goto dequeue;
	}

	if (ichan->status < IPU_CHANNEL_ENABLED) {
		ret = ipu_enable_channel(idmac, ichan);
		if (ret < 0) {
			cookie = ret;
			goto dequeue;
		}
	}

	dump_idmac_reg(ipu);

dequeue:
	if (cookie < 0) {
		spin_lock_irqsave(&ichan->lock, flags);
		list_del_init(&desc->list);
		spin_unlock_irqrestore(&ichan->lock, flags);
		tx->cookie = cookie;
		ichan->dma_chan.cookie = cookie;
	}

out:
	mutex_unlock(&ichan->chan_mutex);

	return cookie;
}