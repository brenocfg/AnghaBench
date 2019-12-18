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
struct sk_buff {int len; scalar_t__ ip_summed; int /*<<< orphan*/  dev; int /*<<< orphan*/  csum; int /*<<< orphan*/  data; } ;
struct iovec {int iov_len; int iov_base; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ __skb_checksum_complete (struct sk_buff*) ; 
 scalar_t__ csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_rx_csum_fault (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_copy_and_csum_datagram (struct sk_buff*,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_copy_datagram_iovec (struct sk_buff*,int,struct iovec*,int) ; 
 scalar_t__ unlikely (int) ; 

int skb_copy_and_csum_datagram_iovec(struct sk_buff *skb,
				     int hlen, struct iovec *iov)
{
	__wsum csum;
	int chunk = skb->len - hlen;

	if (!chunk)
		return 0;

	/* Skip filled elements.
	 * Pretty silly, look at memcpy_toiovec, though 8)
	 */
	while (!iov->iov_len)
		iov++;

	if (iov->iov_len < chunk) {
		if (__skb_checksum_complete(skb))
			goto csum_error;
		if (skb_copy_datagram_iovec(skb, hlen, iov, chunk))
			goto fault;
	} else {
		csum = csum_partial(skb->data, hlen, skb->csum);
		if (skb_copy_and_csum_datagram(skb, hlen, iov->iov_base,
					       chunk, &csum))
			goto fault;
		if (csum_fold(csum))
			goto csum_error;
		if (unlikely(skb->ip_summed == CHECKSUM_COMPLETE))
			netdev_rx_csum_fault(skb->dev);
		iov->iov_len -= chunk;
		iov->iov_base += chunk;
	}
	return 0;
csum_error:
	return -EINVAL;
fault:
	return -EFAULT;
}