#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wlp_tx_hdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct untd_hdr_cmp {scalar_t__ padding; TYPE_1__ hdr; } ;
struct sk_buff {scalar_t__ len; } ;
struct i1480u_tx {struct wlp_tx_hdr* wlp_tx_hdr; struct sk_buff* skb; int /*<<< orphan*/ * buf; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  i1480u_PKT_FRAG_CMP ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  untd_hdr_set_rx_tx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  untd_hdr_set_type (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int i1480u_tx_create_1(struct i1480u_tx *wtx, struct sk_buff *skb,
		       gfp_t gfp_mask)
{
	struct untd_hdr_cmp *untd_hdr_cmp;
	struct wlp_tx_hdr *wlp_tx_hdr;

	wtx->buf = NULL;
	wtx->skb = skb;
	BUG_ON(skb_headroom(skb) < sizeof(*wlp_tx_hdr));
	wlp_tx_hdr = (void *) __skb_push(skb, sizeof(*wlp_tx_hdr));
	wtx->wlp_tx_hdr = wlp_tx_hdr;
	BUG_ON(skb_headroom(skb) < sizeof(*untd_hdr_cmp));
	untd_hdr_cmp = (void *) __skb_push(skb, sizeof(*untd_hdr_cmp));

	untd_hdr_set_type(&untd_hdr_cmp->hdr, i1480u_PKT_FRAG_CMP);
	untd_hdr_set_rx_tx(&untd_hdr_cmp->hdr, 0);
	untd_hdr_cmp->hdr.len = cpu_to_le16(skb->len - sizeof(*untd_hdr_cmp));
	untd_hdr_cmp->padding = 0;
	return 0;
}