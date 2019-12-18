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
struct sk_buff {size_t len; scalar_t__ data; } ;
struct i2400m_msg_hdr {int /*<<< orphan*/ * pld; int /*<<< orphan*/  num_pls; } ;
struct i2400m {int rx_pl_num; int rx_pl_max; int rx_pl_min; size_t rx_size_acc; size_t rx_size_min; size_t rx_size_max; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_num; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  I2400M_PL_ALIGN ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,struct sk_buff*,size_t,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t,unsigned int,int,size_t) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 size_t i2400m_pld_size (int /*<<< orphan*/ *) ; 
 int i2400m_rx_msg_hdr_check (struct i2400m*,struct i2400m_msg_hdr const*,size_t) ; 
 int /*<<< orphan*/  i2400m_rx_payload (struct i2400m*,struct sk_buff*,unsigned int,int /*<<< orphan*/ *,scalar_t__) ; 
 int i2400m_rx_pl_descr_check (struct i2400m*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int i2400m_rx(struct i2400m *i2400m, struct sk_buff *skb)
{
	int i, result;
	struct device *dev = i2400m_dev(i2400m);
	const struct i2400m_msg_hdr *msg_hdr;
	size_t pl_itr, pl_size, skb_len;
	unsigned long flags;
	unsigned num_pls, single_last;

	skb_len = skb->len;
	d_fnstart(4, dev, "(i2400m %p skb %p [size %zu])\n",
		  i2400m, skb, skb_len);
	result = -EIO;
	msg_hdr = (void *) skb->data;
	result = i2400m_rx_msg_hdr_check(i2400m, msg_hdr, skb->len);
	if (result < 0)
		goto error_msg_hdr_check;
	result = -EIO;
	num_pls = le16_to_cpu(msg_hdr->num_pls);
	pl_itr = sizeof(*msg_hdr) +	/* Check payload descriptor(s) */
		num_pls * sizeof(msg_hdr->pld[0]);
	pl_itr = ALIGN(pl_itr, I2400M_PL_ALIGN);
	if (pl_itr > skb->len) {	/* got all the payload descriptors? */
		dev_err(dev, "RX: HW BUG? message too short (%u bytes) for "
			"%u payload descriptors (%zu each, total %zu)\n",
			skb->len, num_pls, sizeof(msg_hdr->pld[0]), pl_itr);
		goto error_pl_descr_short;
	}
	/* Walk each payload payload--check we really got it */
	for (i = 0; i < num_pls; i++) {
		/* work around old gcc warnings */
		pl_size = i2400m_pld_size(&msg_hdr->pld[i]);
		result = i2400m_rx_pl_descr_check(i2400m, &msg_hdr->pld[i],
						  pl_itr, skb->len);
		if (result < 0)
			goto error_pl_descr_check;
		single_last = num_pls == 1 || i == num_pls - 1;
		i2400m_rx_payload(i2400m, skb, single_last, &msg_hdr->pld[i],
				  skb->data + pl_itr);
		pl_itr += ALIGN(pl_size, I2400M_PL_ALIGN);
		cond_resched();		/* Don't monopolize */
	}
	kfree_skb(skb);
	/* Update device statistics */
	spin_lock_irqsave(&i2400m->rx_lock, flags);
	i2400m->rx_pl_num += i;
	if (i > i2400m->rx_pl_max)
		i2400m->rx_pl_max = i;
	if (i < i2400m->rx_pl_min)
		i2400m->rx_pl_min = i;
	i2400m->rx_num++;
	i2400m->rx_size_acc += skb->len;
	if (skb->len < i2400m->rx_size_min)
		i2400m->rx_size_min = skb->len;
	if (skb->len > i2400m->rx_size_max)
		i2400m->rx_size_max = skb->len;
	spin_unlock_irqrestore(&i2400m->rx_lock, flags);
error_pl_descr_check:
error_pl_descr_short:
error_msg_hdr_check:
	d_fnend(4, dev, "(i2400m %p skb %p [size %zu]) = %d\n",
		i2400m, skb, skb_len, result);
	return result;
}