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
struct sk_buff {int* data; } ;
struct libipw_hdr_3addr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_ctl; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_discards_undecryptable; } ;
struct libipw_device {TYPE_2__ ieee_stats; } ;
struct lib80211_crypt_data {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* decrypt_mpdu ) (struct sk_buff*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LIBIPW_DEBUG_DROP (char*,int,...) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int libipw_get_hdrlen (int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
libipw_rx_frame_decrypt(struct libipw_device *ieee, struct sk_buff *skb,
			   struct lib80211_crypt_data *crypt)
{
	struct libipw_hdr_3addr *hdr;
	int res, hdrlen;

	if (crypt == NULL || crypt->ops->decrypt_mpdu == NULL)
		return 0;

	hdr = (struct libipw_hdr_3addr *)skb->data;
	hdrlen = libipw_get_hdrlen(le16_to_cpu(hdr->frame_ctl));

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_mpdu(skb, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	if (res < 0) {
		LIBIPW_DEBUG_DROP("decryption failed (SA=%pM) res=%d\n",
				     hdr->addr2, res);
		if (res == -2)
			LIBIPW_DEBUG_DROP("Decryption failed ICV "
					     "mismatch (key %d)\n",
					     skb->data[hdrlen + 3] >> 6);
		ieee->ieee_stats.rx_discards_undecryptable++;
		return -1;
	}

	return res;
}