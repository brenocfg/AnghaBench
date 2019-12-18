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
typedef  int u32 ;
struct sk_buff {scalar_t__ data; } ;
struct ipath_devdata {int ipath_ibmaxlen; int ipath_flags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int IPATH_4BYTE_TID ; 
 struct sk_buff* __dev_alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

struct sk_buff *ipath_alloc_skb(struct ipath_devdata *dd,
				gfp_t gfp_mask)
{
	struct sk_buff *skb;
	u32 len;

	/*
	 * Only fully supported way to handle this is to allocate lots
	 * extra, align as needed, and then do skb_reserve().  That wastes
	 * a lot of memory...  I'll have to hack this into infinipath_copy
	 * also.
	 */

	/*
	 * We need 2 extra bytes for ipath_ether data sent in the
	 * key header.  In order to keep everything dword aligned,
	 * we'll reserve 4 bytes.
	 */
	len = dd->ipath_ibmaxlen + 4;

	if (dd->ipath_flags & IPATH_4BYTE_TID) {
		/* We need a 2KB multiple alignment, and there is no way
		 * to do it except to allocate extra and then skb_reserve
		 * enough to bring it up to the right alignment.
		 */
		len += 2047;
	}

	skb = __dev_alloc_skb(len, gfp_mask);
	if (!skb) {
		ipath_dev_err(dd, "Failed to allocate skbuff, length %u\n",
			      len);
		goto bail;
	}

	skb_reserve(skb, 4);

	if (dd->ipath_flags & IPATH_4BYTE_TID) {
		u32 una = (unsigned long)skb->data & 2047;
		if (una)
			skb_reserve(skb, 2048 - una);
	}

bail:
	return skb;
}