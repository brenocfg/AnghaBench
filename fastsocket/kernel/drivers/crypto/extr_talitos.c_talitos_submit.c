#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct talitos_request {void (* callback ) (struct device*,struct talitos_desc*,void*,int) ;int /*<<< orphan*/  dma_desc; struct talitos_desc* desc; void* context; } ;
struct talitos_private {int num_channels; int fifo_len; TYPE_1__* chan; scalar_t__ reg; int /*<<< orphan*/  last_chan; } ;
struct talitos_desc {int /*<<< orphan*/  hdr; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int head; int /*<<< orphan*/  head_lock; struct talitos_request* fifo; int /*<<< orphan*/  submit_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_HDR_DONE_NOTIFY ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EAGAIN ; 
 int EINPROGRESS ; 
 scalar_t__ TALITOS_FF (unsigned long) ; 
 scalar_t__ TALITOS_FF_LO (unsigned long) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,struct talitos_desc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int talitos_submit(struct device *dev, struct talitos_desc *desc,
			  void (*callback)(struct device *dev,
					   struct talitos_desc *desc,
					   void *context, int error),
			  void *context)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	struct talitos_request *request;
	unsigned long flags, ch;
	int head;

	/* select done notification */
	desc->hdr |= DESC_HDR_DONE_NOTIFY;

	/* emulate SEC's round-robin channel fifo polling scheme */
	ch = atomic_inc_return(&priv->last_chan) & (priv->num_channels - 1);

	spin_lock_irqsave(&priv->chan[ch].head_lock, flags);

	if (!atomic_inc_not_zero(&priv->chan[ch].submit_count)) {
		/* h/w fifo is full */
		spin_unlock_irqrestore(&priv->chan[ch].head_lock, flags);
		return -EAGAIN;
	}

	head = priv->chan[ch].head;
	request = &priv->chan[ch].fifo[head];

	/* map descriptor and save caller data */
	request->dma_desc = dma_map_single(dev, desc, sizeof(*desc),
					   DMA_BIDIRECTIONAL);
	request->callback = callback;
	request->context = context;

	/* increment fifo head */
	priv->chan[ch].head = (priv->chan[ch].head + 1) & (priv->fifo_len - 1);

	smp_wmb();
	request->desc = desc;

	/* GO! */
	wmb();
	out_be32(priv->reg + TALITOS_FF(ch),
		 cpu_to_be32(upper_32_bits(request->dma_desc)));
	out_be32(priv->reg + TALITOS_FF_LO(ch),
		 cpu_to_be32(lower_32_bits(request->dma_desc)));

	spin_unlock_irqrestore(&priv->chan[ch].head_lock, flags);

	return -EINPROGRESS;
}