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
typedef  int /*<<< orphan*/  uint ;
struct sk_buff {scalar_t__ len; scalar_t__ data_len; struct sk_buff* next; } ;
struct cxgbi_sock {scalar_t__ state; int err; scalar_t__ write_seq; scalar_t__ snd_una; int /*<<< orphan*/  lock; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; struct cxgbi_device* cdev; } ;
struct cxgbi_device {scalar_t__ snd_win; scalar_t__ skb_tx_rsvd; int /*<<< orphan*/  (* csk_push_tx_frames ) (struct cxgbi_sock*,int) ;} ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 scalar_t__ CTP_ESTABLISHED ; 
 int CXGBI_DBG_PDU_TX ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int EPIPE ; 
 int SKB_WR_LIST_SIZE ; 
 int /*<<< orphan*/  SKCBF_TX_NEED_HDR ; 
 int /*<<< orphan*/  cxgbi_skcb_set_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_skcb_ulp_mode (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbi_sock_skb_entail (struct cxgbi_sock*,struct sk_buff*) ; 
 scalar_t__ cxgbi_ulp_extra_len (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*,struct cxgbi_sock*,int,scalar_t__,...) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cxgbi_sock*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cxgbi_sock_send_pdus(struct cxgbi_sock *csk, struct sk_buff *skb)
{
	struct cxgbi_device *cdev = csk->cdev;
	struct sk_buff *next;
	int err, copied = 0;

	spin_lock_bh(&csk->lock);

	if (csk->state != CTP_ESTABLISHED) {
		log_debug(1 << CXGBI_DBG_PDU_TX,
			"csk 0x%p,%u,0x%lx,%u, EAGAIN.\n",
			csk, csk->state, csk->flags, csk->tid);
		err = -EAGAIN;
		goto out_err;
	}

	if (csk->err) {
		log_debug(1 << CXGBI_DBG_PDU_TX,
			"csk 0x%p,%u,0x%lx,%u, EPIPE %d.\n",
			csk, csk->state, csk->flags, csk->tid, csk->err);
		err = -EPIPE;
		goto out_err;
	}

	if (csk->write_seq - csk->snd_una >= cdev->snd_win) {
		log_debug(1 << CXGBI_DBG_PDU_TX,
			"csk 0x%p,%u,0x%lx,%u, FULL %u-%u >= %u.\n",
			csk, csk->state, csk->flags, csk->tid, csk->write_seq,
			csk->snd_una, cdev->snd_win);
		err = -ENOBUFS;
		goto out_err;
	}

	while (skb) {
		int frags = skb_shinfo(skb)->nr_frags +
				(skb->len != skb->data_len);

		if (unlikely(skb_headroom(skb) < cdev->skb_tx_rsvd)) {
			pr_err("csk 0x%p, skb head %u < %u.\n",
				csk, skb_headroom(skb), cdev->skb_tx_rsvd);
			err = -EINVAL;
			goto out_err;
		}

		if (frags >= SKB_WR_LIST_SIZE) {
			pr_err("csk 0x%p, frags %d, %u,%u >%u.\n",
				csk, skb_shinfo(skb)->nr_frags, skb->len,
				skb->data_len, (uint)(SKB_WR_LIST_SIZE));
			err = -EINVAL;
			goto out_err;
		}

		next = skb->next;
		skb->next = NULL;
		cxgbi_skcb_set_flag(skb, SKCBF_TX_NEED_HDR);
		cxgbi_sock_skb_entail(csk, skb);
		copied += skb->len;
		csk->write_seq += skb->len +
				cxgbi_ulp_extra_len(cxgbi_skcb_ulp_mode(skb));
		skb = next;
	}
done:
	if (likely(skb_queue_len(&csk->write_queue)))
		cdev->csk_push_tx_frames(csk, 1);
	spin_unlock_bh(&csk->lock);
	return copied;

out_err:
	if (copied == 0 && err == -EPIPE)
		copied = csk->err ? csk->err : -EPIPE;
	else
		copied = err;
	goto done;
}