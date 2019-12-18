#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned long len; int /*<<< orphan*/  users; struct ll_header* data; int /*<<< orphan*/  protocol; } ;
struct net_device {struct ctcm_priv* ml_priv; } ;
struct ll_header {int length; scalar_t__ unused; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct ctcm_priv {TYPE_1__ stats; } ;
struct TYPE_6__ {unsigned long txlen; int /*<<< orphan*/  doios_single; int /*<<< orphan*/  send_stamp; } ;
struct channel {int collect_len; int max_bufsize; struct net_device* netdev; int /*<<< orphan*/  io_queue; int /*<<< orphan*/  timer; TYPE_2__ prof; int /*<<< orphan*/  cdev; TYPE_3__* ccw; int /*<<< orphan*/  fsm; scalar_t__ retry; struct sk_buff* trans_skb; int /*<<< orphan*/  collect_lock; int /*<<< orphan*/  collect_queue; } ;
typedef  int __u16 ;
struct TYPE_7__ {int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_TIME_5_SEC ; 
 int /*<<< orphan*/  CTC_EVENT_TIMER ; 
 int /*<<< orphan*/  CTC_STATE_TX ; 
 scalar_t__ CTC_STATE_TXIDLE ; 
 int EBUSY ; 
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int GFP_DMA ; 
 unsigned long LL_HEADER_LENGTH ; 
 struct sk_buff* alloc_skb (int,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int ccw_device_start (int /*<<< orphan*/ ,TYPE_3__*,unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctcm_ccw_check_rc (struct channel*,int,char*) ; 
 scalar_t__ ctcm_checkalloc_buffer (struct channel*) ; 
 int /*<<< orphan*/  ctcm_clear_busy (struct net_device*) ; 
 int /*<<< orphan*/  current_kernel_time () ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  fsm_addtimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct channel*) ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 scalar_t__ fsm_getstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct ll_header*,unsigned long) ; 
 scalar_t__ set_normalized_cda (TYPE_3__*,struct ll_header*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_dequeue_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,unsigned long) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_tail_pointer (struct sk_buff*) ; 
 scalar_t__ skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ctcm_transmit_skb(struct channel *ch, struct sk_buff *skb)
{
	unsigned long saveflags;
	struct ll_header header;
	int rc = 0;
	__u16 block_len;
	int ccw_idx;
	struct sk_buff *nskb;
	unsigned long hi;

	/* we need to acquire the lock for testing the state
	 * otherwise we can have an IRQ changing the state to
	 * TXIDLE after the test but before acquiring the lock.
	 */
	spin_lock_irqsave(&ch->collect_lock, saveflags);
	if (fsm_getstate(ch->fsm) != CTC_STATE_TXIDLE) {
		int l = skb->len + LL_HEADER_LENGTH;

		if (ch->collect_len + l > ch->max_bufsize - 2) {
			spin_unlock_irqrestore(&ch->collect_lock, saveflags);
			return -EBUSY;
		} else {
			atomic_inc(&skb->users);
			header.length = l;
			header.type = skb->protocol;
			header.unused = 0;
			memcpy(skb_push(skb, LL_HEADER_LENGTH), &header,
			       LL_HEADER_LENGTH);
			skb_queue_tail(&ch->collect_queue, skb);
			ch->collect_len += l;
		}
		spin_unlock_irqrestore(&ch->collect_lock, saveflags);
				goto done;
	}
	spin_unlock_irqrestore(&ch->collect_lock, saveflags);
	/*
	 * Protect skb against beeing free'd by upper
	 * layers.
	 */
	atomic_inc(&skb->users);
	ch->prof.txlen += skb->len;
	header.length = skb->len + LL_HEADER_LENGTH;
	header.type = skb->protocol;
	header.unused = 0;
	memcpy(skb_push(skb, LL_HEADER_LENGTH), &header, LL_HEADER_LENGTH);
	block_len = skb->len + 2;
	*((__u16 *)skb_push(skb, 2)) = block_len;

	/*
	 * IDAL support in CTCM is broken, so we have to
	 * care about skb's above 2G ourselves.
	 */
	hi = ((unsigned long)skb_tail_pointer(skb) + LL_HEADER_LENGTH) >> 31;
	if (hi) {
		nskb = alloc_skb(skb->len, GFP_ATOMIC | GFP_DMA);
		if (!nskb) {
			atomic_dec(&skb->users);
			skb_pull(skb, LL_HEADER_LENGTH + 2);
			ctcm_clear_busy(ch->netdev);
			return -ENOMEM;
		} else {
			memcpy(skb_put(nskb, skb->len), skb->data, skb->len);
			atomic_inc(&nskb->users);
			atomic_dec(&skb->users);
			dev_kfree_skb_irq(skb);
			skb = nskb;
		}
	}

	ch->ccw[4].count = block_len;
	if (set_normalized_cda(&ch->ccw[4], skb->data)) {
		/*
		 * idal allocation failed, try via copying to
		 * trans_skb. trans_skb usually has a pre-allocated
		 * idal.
		 */
		if (ctcm_checkalloc_buffer(ch)) {
			/*
			 * Remove our header. It gets added
			 * again on retransmit.
			 */
			atomic_dec(&skb->users);
			skb_pull(skb, LL_HEADER_LENGTH + 2);
			ctcm_clear_busy(ch->netdev);
			return -ENOMEM;
		}

		skb_reset_tail_pointer(ch->trans_skb);
		ch->trans_skb->len = 0;
		ch->ccw[1].count = skb->len;
		skb_copy_from_linear_data(skb,
				skb_put(ch->trans_skb, skb->len), skb->len);
		atomic_dec(&skb->users);
		dev_kfree_skb_irq(skb);
		ccw_idx = 0;
	} else {
		skb_queue_tail(&ch->io_queue, skb);
		ccw_idx = 3;
	}
	ch->retry = 0;
	fsm_newstate(ch->fsm, CTC_STATE_TX);
	fsm_addtimer(&ch->timer, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);
	spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
	ch->prof.send_stamp = current_kernel_time(); /* xtime */
	rc = ccw_device_start(ch->cdev, &ch->ccw[ccw_idx],
					(unsigned long)ch, 0xff, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev), saveflags);
	if (ccw_idx == 3)
		ch->prof.doios_single++;
	if (rc != 0) {
		fsm_deltimer(&ch->timer);
		ctcm_ccw_check_rc(ch, rc, "single skb TX");
		if (ccw_idx == 3)
			skb_dequeue_tail(&ch->io_queue);
		/*
		 * Remove our header. It gets added
		 * again on retransmit.
		 */
		skb_pull(skb, LL_HEADER_LENGTH + 2);
	} else if (ccw_idx == 0) {
		struct net_device *dev = ch->netdev;
		struct ctcm_priv *priv = dev->ml_priv;
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += skb->len - LL_HEADER_LENGTH;
	}
done:
	ctcm_clear_busy(ch->netdev);
	return rc;
}