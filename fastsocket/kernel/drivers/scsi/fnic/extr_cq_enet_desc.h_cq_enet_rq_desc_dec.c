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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct cq_enet_rq_desc {int completed_index_flags; int q_number_rss_type_flags; int bytes_written_flags; int vlan; int checksum_fcoe; int flags; int /*<<< orphan*/  rss_hash; } ;
struct cq_desc {int dummy; } ;

/* Variables and functions */
 int CQ_DESC_Q_NUM_BITS ; 
 int CQ_ENET_RQ_DESC_BYTES_WRITTEN_MASK ; 
 int CQ_ENET_RQ_DESC_FCOE_ENC_ERROR ; 
 int CQ_ENET_RQ_DESC_FCOE_EOF_MASK ; 
 int CQ_ENET_RQ_DESC_FCOE_EOF_SHIFT ; 
 int CQ_ENET_RQ_DESC_FCOE_FC_CRC_OK ; 
 int CQ_ENET_RQ_DESC_FCOE_SOF_MASK ; 
 int CQ_ENET_RQ_DESC_FLAGS_CSUM_NOT_CALC ; 
 int CQ_ENET_RQ_DESC_FLAGS_EOP ; 
 int CQ_ENET_RQ_DESC_FLAGS_FCOE ; 
 int CQ_ENET_RQ_DESC_FLAGS_FCS_OK ; 
 int CQ_ENET_RQ_DESC_FLAGS_INGRESS_PORT ; 
 int CQ_ENET_RQ_DESC_FLAGS_IPV4 ; 
 int CQ_ENET_RQ_DESC_FLAGS_IPV4_CSUM_OK ; 
 int CQ_ENET_RQ_DESC_FLAGS_IPV4_FRAGMENT ; 
 int CQ_ENET_RQ_DESC_FLAGS_IPV6 ; 
 int CQ_ENET_RQ_DESC_FLAGS_SOP ; 
 int CQ_ENET_RQ_DESC_FLAGS_TCP ; 
 int CQ_ENET_RQ_DESC_FLAGS_TCP_UDP_CSUM_OK ; 
 int CQ_ENET_RQ_DESC_FLAGS_TRUNCATED ; 
 int CQ_ENET_RQ_DESC_FLAGS_UDP ; 
 int CQ_ENET_RQ_DESC_FLAGS_VLAN_STRIPPED ; 
 int CQ_ENET_RQ_DESC_RSS_TYPE_MASK ; 
 int /*<<< orphan*/  cq_desc_dec (struct cq_desc*,int*,int*,int*,int*) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cq_enet_rq_desc_dec(struct cq_enet_rq_desc *desc,
	u8 *type, u8 *color, u16 *q_number, u16 *completed_index,
	u8 *ingress_port, u8 *fcoe, u8 *eop, u8 *sop, u8 *rss_type,
	u8 *csum_not_calc, u32 *rss_hash, u16 *bytes_written, u8 *packet_error,
	u8 *vlan_stripped, u16 *vlan, u16 *checksum, u8 *fcoe_sof,
	u8 *fcoe_fc_crc_ok, u8 *fcoe_enc_error, u8 *fcoe_eof,
	u8 *tcp_udp_csum_ok, u8 *udp, u8 *tcp, u8 *ipv4_csum_ok,
	u8 *ipv6, u8 *ipv4, u8 *ipv4_fragment, u8 *fcs_ok)
{
	u16 completed_index_flags = le16_to_cpu(desc->completed_index_flags);
	u16 q_number_rss_type_flags =
		le16_to_cpu(desc->q_number_rss_type_flags);
	u16 bytes_written_flags = le16_to_cpu(desc->bytes_written_flags);

	cq_desc_dec((struct cq_desc *)desc, type,
		color, q_number, completed_index);

	*ingress_port = (completed_index_flags &
		CQ_ENET_RQ_DESC_FLAGS_INGRESS_PORT) ? 1 : 0;
	*fcoe = (completed_index_flags & CQ_ENET_RQ_DESC_FLAGS_FCOE) ?
		1 : 0;
	*eop = (completed_index_flags & CQ_ENET_RQ_DESC_FLAGS_EOP) ?
		1 : 0;
	*sop = (completed_index_flags & CQ_ENET_RQ_DESC_FLAGS_SOP) ?
		1 : 0;

	*rss_type = (u8)((q_number_rss_type_flags >> CQ_DESC_Q_NUM_BITS) &
		CQ_ENET_RQ_DESC_RSS_TYPE_MASK);
	*csum_not_calc = (q_number_rss_type_flags &
		CQ_ENET_RQ_DESC_FLAGS_CSUM_NOT_CALC) ? 1 : 0;

	*rss_hash = le32_to_cpu(desc->rss_hash);

	*bytes_written = bytes_written_flags &
		CQ_ENET_RQ_DESC_BYTES_WRITTEN_MASK;
	*packet_error = (bytes_written_flags &
		CQ_ENET_RQ_DESC_FLAGS_TRUNCATED) ? 1 : 0;
	*vlan_stripped = (bytes_written_flags &
		CQ_ENET_RQ_DESC_FLAGS_VLAN_STRIPPED) ? 1 : 0;

	*vlan = le16_to_cpu(desc->vlan);

	if (*fcoe) {
		*fcoe_sof = (u8)(le16_to_cpu(desc->checksum_fcoe) &
			CQ_ENET_RQ_DESC_FCOE_SOF_MASK);
		*fcoe_fc_crc_ok = (desc->flags &
			CQ_ENET_RQ_DESC_FCOE_FC_CRC_OK) ? 1 : 0;
		*fcoe_enc_error = (desc->flags &
			CQ_ENET_RQ_DESC_FCOE_ENC_ERROR) ? 1 : 0;
		*fcoe_eof = (u8)((desc->checksum_fcoe >>
			CQ_ENET_RQ_DESC_FCOE_EOF_SHIFT) &
			CQ_ENET_RQ_DESC_FCOE_EOF_MASK);
		*checksum = 0;
	} else {
		*fcoe_sof = 0;
		*fcoe_fc_crc_ok = 0;
		*fcoe_enc_error = 0;
		*fcoe_eof = 0;
		*checksum = le16_to_cpu(desc->checksum_fcoe);
	}

	*tcp_udp_csum_ok =
		(desc->flags & CQ_ENET_RQ_DESC_FLAGS_TCP_UDP_CSUM_OK) ? 1 : 0;
	*udp = (desc->flags & CQ_ENET_RQ_DESC_FLAGS_UDP) ? 1 : 0;
	*tcp = (desc->flags & CQ_ENET_RQ_DESC_FLAGS_TCP) ? 1 : 0;
	*ipv4_csum_ok =
		(desc->flags & CQ_ENET_RQ_DESC_FLAGS_IPV4_CSUM_OK) ? 1 : 0;
	*ipv6 = (desc->flags & CQ_ENET_RQ_DESC_FLAGS_IPV6) ? 1 : 0;
	*ipv4 = (desc->flags & CQ_ENET_RQ_DESC_FLAGS_IPV4) ? 1 : 0;
	*ipv4_fragment =
		(desc->flags & CQ_ENET_RQ_DESC_FLAGS_IPV4_FRAGMENT) ? 1 : 0;
	*fcs_ok = (desc->flags & CQ_ENET_RQ_DESC_FLAGS_FCS_OK) ? 1 : 0;
}