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
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {int len; scalar_t__ mac_len; } ;
struct ixgbe_tx_buffer {int bytecount; int tx_flags; int /*<<< orphan*/  gso_segs; struct sk_buff* skb; } ;
struct ixgbe_ring {int /*<<< orphan*/  dev; } ;
struct fcoe_hdr {int fcoe_sof; } ;
struct fcoe_crc_eof {int dummy; } ;
struct fc_frame_header {int* fh_f_ctl; } ;
struct TYPE_2__ {scalar_t__ gso_type; int gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
#define  FC_EOF_A 135 
#define  FC_EOF_N 134 
#define  FC_EOF_NI 133 
#define  FC_EOF_T 132 
 int FC_FC_REL_OFF ; 
#define  FC_SOF_I2 131 
#define  FC_SOF_I3 130 
#define  FC_SOF_N2 129 
#define  FC_SOF_N3 128 
 int IXGBE_ADVTXD_FCOEF_EOF_A ; 
 int IXGBE_ADVTXD_FCOEF_EOF_N ; 
 int IXGBE_ADVTXD_FCOEF_EOF_NI ; 
 int IXGBE_ADVTXD_FCOEF_EOF_T ; 
 int IXGBE_ADVTXD_FCOEF_ORIE ; 
 int IXGBE_ADVTXD_FCOEF_ORIS ; 
 int IXGBE_ADVTXD_FCOEF_PARINC ; 
 int IXGBE_ADVTXD_FCOEF_SOF ; 
 int IXGBE_ADVTXD_MACLEN_SHIFT ; 
 int IXGBE_ADVTXD_MSS_SHIFT ; 
 int /*<<< orphan*/  IXGBE_ADVTXT_TUCMD_FCOE ; 
 int IXGBE_TX_FLAGS_CC ; 
 int IXGBE_TX_FLAGS_FCOE ; 
 int IXGBE_TX_FLAGS_TSO ; 
 int IXGBE_TX_FLAGS_VLAN_MASK ; 
 scalar_t__ SKB_GSO_FCOE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ixgbe_tx_ctxtdesc (struct ixgbe_ring*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int,int*,int) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,scalar_t__) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 

int ixgbe_fso(struct ixgbe_ring *tx_ring,
	      struct ixgbe_tx_buffer *first,
	      u8 *hdr_len)
{
	struct sk_buff *skb = first->skb;
	struct fc_frame_header *fh;
	u32 vlan_macip_lens;
	u32 fcoe_sof_eof = 0;
	u32 mss_l4len_idx;
	u8 sof, eof;

	if (skb_is_gso(skb) && (skb_shinfo(skb)->gso_type != SKB_GSO_FCOE)) {
		dev_err(tx_ring->dev, "Wrong gso type %d:expecting SKB_GSO_FCOE\n",
			skb_shinfo(skb)->gso_type);
		return -EINVAL;
	}

	/* resets the header to point fcoe/fc */
	skb_set_network_header(skb, skb->mac_len);
	skb_set_transport_header(skb, skb->mac_len +
				 sizeof(struct fcoe_hdr));

	/* sets up SOF and ORIS */
	sof = ((struct fcoe_hdr *)skb_network_header(skb))->fcoe_sof;
	switch (sof) {
	case FC_SOF_I2:
		fcoe_sof_eof = IXGBE_ADVTXD_FCOEF_ORIS;
		break;
	case FC_SOF_I3:
		fcoe_sof_eof = IXGBE_ADVTXD_FCOEF_SOF |
			       IXGBE_ADVTXD_FCOEF_ORIS;
		break;
	case FC_SOF_N2:
		break;
	case FC_SOF_N3:
		fcoe_sof_eof = IXGBE_ADVTXD_FCOEF_SOF;
		break;
	default:
		dev_warn(tx_ring->dev, "unknown sof = 0x%x\n", sof);
		return -EINVAL;
	}

	/* the first byte of the last dword is EOF */
	skb_copy_bits(skb, skb->len - 4, &eof, 1);
	/* sets up EOF and ORIE */
	switch (eof) {
	case FC_EOF_N:
		fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_EOF_N;
		break;
	case FC_EOF_T:
		/* lso needs ORIE */
		if (skb_is_gso(skb))
			fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_EOF_N |
					IXGBE_ADVTXD_FCOEF_ORIE;
		else
			fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_EOF_T;
		break;
	case FC_EOF_NI:
		fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_EOF_NI;
		break;
	case FC_EOF_A:
		fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_EOF_A;
		break;
	default:
		dev_warn(tx_ring->dev, "unknown eof = 0x%x\n", eof);
		return -EINVAL;
	}

	/* sets up PARINC indicating data offset */
	fh = (struct fc_frame_header *)skb_transport_header(skb);
	if (fh->fh_f_ctl[2] & FC_FC_REL_OFF)
		fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_PARINC;

	/* include trailer in headlen as it is replicated per frame */
	*hdr_len = sizeof(struct fcoe_crc_eof);

	/* hdr_len includes fc_hdr if FCoE LSO is enabled */
	if (skb_is_gso(skb)) {
		*hdr_len += skb_transport_offset(skb) +
			    sizeof(struct fc_frame_header);
		/* update gso_segs and bytecount */
		first->gso_segs = DIV_ROUND_UP(skb->len - *hdr_len,
					       skb_shinfo(skb)->gso_size);
		first->bytecount += (first->gso_segs - 1) * *hdr_len;
		first->tx_flags |= IXGBE_TX_FLAGS_TSO;
	}

	/* set flag indicating FCOE to ixgbe_tx_map call */
	first->tx_flags |= IXGBE_TX_FLAGS_FCOE | IXGBE_TX_FLAGS_CC;

	/* mss_l4len_id: use 0 for FSO as TSO, no need for L4LEN */
	mss_l4len_idx = skb_shinfo(skb)->gso_size << IXGBE_ADVTXD_MSS_SHIFT;

	/* vlan_macip_lens: HEADLEN, MACLEN, VLAN tag */
	vlan_macip_lens = skb_transport_offset(skb) +
			  sizeof(struct fc_frame_header);
	vlan_macip_lens |= (skb_transport_offset(skb) - 4)
			   << IXGBE_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IXGBE_TX_FLAGS_VLAN_MASK;

	/* write context desc */
	ixgbe_tx_ctxtdesc(tx_ring, vlan_macip_lens, fcoe_sof_eof,
			  IXGBE_ADVTXT_TUCMD_FCOE, mss_l4len_idx);

	return 0;
}