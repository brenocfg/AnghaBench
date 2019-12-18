#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_allocation; int sk_shutdown; scalar_t__ sk_sndbuf; TYPE_1__* sk_socket; int /*<<< orphan*/  sk_wmem_alloc; } ;
struct sk_buff {unsigned long truesize; } ;
struct page {int dummy; } ;
struct TYPE_5__ {int size; scalar_t__ page_offset; struct page* page; } ;
typedef  TYPE_2__ skb_frag_t ;
typedef  int gfp_t ;
struct TYPE_6__ {int nr_frags; TYPE_2__* frags; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int EPIPE ; 
 int MAX_SKB_FRAGS ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int __GFP_REPEAT ; 
 int __GFP_WAIT ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (unsigned long,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int sock_error (struct sock*) ; 
 int sock_intr_errno (long) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 long sock_wait_for_wmem (struct sock*,long) ; 

struct sk_buff *sock_alloc_send_pskb(struct sock *sk, unsigned long header_len,
				     unsigned long data_len, int noblock,
				     int *errcode)
{
	struct sk_buff *skb;
	gfp_t gfp_mask;
	long timeo;
	int err;

	gfp_mask = sk->sk_allocation;
	if (gfp_mask & __GFP_WAIT)
		gfp_mask |= __GFP_REPEAT;

	timeo = sock_sndtimeo(sk, noblock);
	while (1) {
		int npages;
		err = sock_error(sk);
		if (err != 0)
			goto failure;

		err = -EPIPE;
		if (sk->sk_shutdown & SEND_SHUTDOWN)
			goto failure;

		err = -EMSGSIZE;
		npages = (data_len + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
		if (npages > MAX_SKB_FRAGS)
			goto failure;

		if (atomic_read(&sk->sk_wmem_alloc) < sk->sk_sndbuf) {
			skb = alloc_skb(header_len, gfp_mask);
			if (skb) {
				int i;

				/* No pages, we're done... */
				if (!data_len)
					break;

				skb->truesize += data_len;
				skb_shinfo(skb)->nr_frags = npages;
				for (i = 0; i < npages; i++) {
					struct page *page;
					skb_frag_t *frag;

					page = alloc_pages(sk->sk_allocation, 0);
					if (!page) {
						err = -ENOBUFS;
						skb_shinfo(skb)->nr_frags = i;
						kfree_skb(skb);
						goto failure;
					}

					frag = &skb_shinfo(skb)->frags[i];
					frag->page = page;
					frag->page_offset = 0;
					frag->size = (data_len >= PAGE_SIZE ?
						      PAGE_SIZE :
						      data_len);
					data_len -= PAGE_SIZE;
				}

				/* Full success... */
				break;
			}
			err = -ENOBUFS;
			goto failure;
		}
		set_bit(SOCK_ASYNC_NOSPACE, &sk->sk_socket->flags);
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		err = -EAGAIN;
		if (!timeo)
			goto failure;
		if (signal_pending(current))
			goto interrupted;
		timeo = sock_wait_for_wmem(sk, timeo);
	}

	skb_set_owner_w(skb, sk);
	return skb;

interrupted:
	err = sock_intr_errno(timeo);
failure:
	*errcode = err;
	return NULL;
}