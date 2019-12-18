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
struct talitos_request {int /*<<< orphan*/  context; TYPE_2__* desc; int /*<<< orphan*/  (* callback ) (struct device*,TYPE_2__*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  dma_desc; } ;
struct talitos_private {int fifo_len; TYPE_1__* chan; } ;
struct talitos_desc {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int hdr; } ;
struct TYPE_3__ {int tail; int /*<<< orphan*/  tail_lock; int /*<<< orphan*/  submit_count; struct talitos_request* fifo; } ;

/* Variables and functions */
 int DESC_HDR_DONE ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct device*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void flush_channel(struct device *dev, int ch, int error, int reset_ch)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	struct talitos_request *request, saved_req;
	unsigned long flags;
	int tail, status;

	spin_lock_irqsave(&priv->chan[ch].tail_lock, flags);

	tail = priv->chan[ch].tail;
	while (priv->chan[ch].fifo[tail].desc) {
		request = &priv->chan[ch].fifo[tail];

		/* descriptors with their done bits set don't get the error */
		rmb();
		if ((request->desc->hdr & DESC_HDR_DONE) == DESC_HDR_DONE)
			status = 0;
		else
			if (!error)
				break;
			else
				status = error;

		dma_unmap_single(dev, request->dma_desc,
				 sizeof(struct talitos_desc),
				 DMA_BIDIRECTIONAL);

		/* copy entries so we can call callback outside lock */
		saved_req.desc = request->desc;
		saved_req.callback = request->callback;
		saved_req.context = request->context;

		/* release request entry in fifo */
		smp_wmb();
		request->desc = NULL;

		/* increment fifo tail */
		priv->chan[ch].tail = (tail + 1) & (priv->fifo_len - 1);

		spin_unlock_irqrestore(&priv->chan[ch].tail_lock, flags);

		atomic_dec(&priv->chan[ch].submit_count);

		saved_req.callback(dev, saved_req.desc, saved_req.context,
				   status);
		/* channel may resume processing in single desc error case */
		if (error && !reset_ch && status == error)
			return;
		spin_lock_irqsave(&priv->chan[ch].tail_lock, flags);
		tail = priv->chan[ch].tail;
	}

	spin_unlock_irqrestore(&priv->chan[ch].tail_lock, flags);
}