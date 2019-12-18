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
struct vlan_ethhdr {scalar_t__ h_vlan_proto; scalar_t__ h_vlan_encapsulated_proto; } ;
struct sk_buff {int mac_len; scalar_t__ protocol; int /*<<< orphan*/  len; scalar_t__ data; struct sk_buff* next; scalar_t__ encapsulation; } ;
struct gre_base_hdr {int flags; scalar_t__ protocol; } ;
typedef  int /*<<< orphan*/  __sum16 ;
typedef  scalar_t__ __be32 ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 int EINVAL ; 
 struct sk_buff* ERR_PTR (int) ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_TEB ; 
 int GRE_CSUM ; 
 int GRE_HEADER_SECTION ; 
 int GRE_KEY ; 
 int GRE_SEQ ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int NETIF_F_SG ; 
 int SKB_GSO_DODGY ; 
 int SKB_GSO_GRE ; 
 int SKB_GSO_TCPV4 ; 
 int SKB_GSO_TCPV6 ; 
 int SKB_GSO_TCP_ECN ; 
 int SKB_GSO_UDP ; 
 int VLAN_ETH_HLEN ; 
 scalar_t__ VLAN_HLEN ; 
 int __skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  csum_fold (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netif_skb_features (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_has_shared_frag (struct sk_buff*) ; 
 struct sk_buff* skb_mac_gso_segment (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_tnl_header_len (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *gre_gso_segment(struct sk_buff *skb,
				       int features)
{
	struct sk_buff *segs = ERR_PTR(-EINVAL);
	int ghl = GRE_HEADER_SECTION;
	struct gre_base_hdr *greh;
	int mac_len = skb->mac_len;
	__be16 protocol = skb->protocol;
	int inner_mac_len = 0;
	int tnl_hlen;
	bool csum;

	if (unlikely(skb_shinfo(skb)->gso_type &
				~(SKB_GSO_TCPV4 |
				  SKB_GSO_TCPV6 |
				  SKB_GSO_UDP |
				  SKB_GSO_DODGY |
				  SKB_GSO_TCP_ECN |
				  SKB_GSO_GRE)))
		goto out;

	if (unlikely(!pskb_may_pull(skb, sizeof(*greh))))
		goto out;

	greh = (struct gre_base_hdr *)skb_transport_header(skb);

	if (greh->flags & GRE_KEY)
		ghl += GRE_HEADER_SECTION;
	if (greh->flags & GRE_SEQ)
		ghl += GRE_HEADER_SECTION;
	if (greh->flags & GRE_CSUM) {
		ghl += GRE_HEADER_SECTION;
		csum = true;
	} else
		csum = false;

	/* RHEL specific
	 *
	 * Due to lack of inner header marks in struct sk_buff, the
	 * only way to regain knowledge of the inner header protocol
	 * and inner mac header boundry is by packet inspection.
	 */
	if (greh->protocol == htons(ETH_P_TEB)) {
		struct vlan_ethhdr *veth;

		if (unlikely(!pskb_may_pull(skb, ghl + ETH_HLEN)))
			goto out;

		veth = (struct vlan_ethhdr *) (skb->data + ghl);
		inner_mac_len = ETH_HLEN;

		if (veth->h_vlan_proto == htons(ETH_P_8021Q)) {
			if (unlikely(!pskb_may_pull(skb, ghl + VLAN_ETH_HLEN)))
				goto out;

			skb->protocol = veth->h_vlan_encapsulated_proto;
			inner_mac_len += VLAN_HLEN;
		} else
			skb->protocol = veth->h_vlan_proto;
	} else {
		skb->protocol = greh->protocol;

		if (unlikely(!pskb_may_pull(skb, ghl)))
			goto out;
	}

	skb->encapsulation = 0;

	__skb_pull(skb, ghl);
	skb_reset_mac_header(skb);

	skb_set_network_header(skb, inner_mac_len);
	skb->mac_len = inner_mac_len;

	/* segment inner packet. */
	/* enc_features = skb->dev->hw_enc_features & netif_skb_features(skb);
	 * No hardware supports HW GRE TSO offload yet, fall back to software GSO
	 */
	segs = skb_mac_gso_segment(skb, NETIF_F_SG & netif_skb_features(skb));
	if (!segs || IS_ERR(segs))
		goto out;

	skb = segs;
	tnl_hlen = skb_tnl_header_len(skb);
	do {
		__skb_push(skb, ghl);
		if (csum) {
			__be32 *pcsum;

			if (skb_has_shared_frag(skb)) {
				int err;

				err = __skb_linearize(skb);
				if (err) {
					kfree_skb(segs);
					segs = ERR_PTR(err);
					goto out;
				}
			}

			greh = (struct gre_base_hdr *)(skb->data);
			pcsum = (__be32 *)(greh + 1);
			*pcsum = 0;
			*(__sum16 *)pcsum = csum_fold(skb_checksum(skb, 0, skb->len, 0));
		}
		__skb_push(skb, tnl_hlen - ghl);

		skb_reset_mac_header(skb);
		skb_set_network_header(skb, mac_len);
		skb->mac_len = mac_len;
		skb->protocol = protocol;
	} while ((skb = skb->next));
out:
	return segs;
}