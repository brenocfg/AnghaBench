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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct timeval {int dummy; } ;
struct socket {scalar_t__ so_pcb; } ;
struct mbuf {int m_flags; struct mbuf* m_next; } ;
struct inpcb {int inp_vflag; } ;
struct in_addr {int /*<<< orphan*/  member_0; } ;
struct in6_addr {int dummy; } ;
struct content_filter {int cf_flags; int /*<<< orphan*/  cf_kcunit; int /*<<< orphan*/  cf_kcref; } ;
struct TYPE_5__ {size_t cfm_len; int cfm_version; int /*<<< orphan*/  cfm_op; int /*<<< orphan*/  cfm_sock_id; int /*<<< orphan*/  cfm_type; } ;
struct cfil_msg_data_event {TYPE_2__ cfd_msghdr; int /*<<< orphan*/  cfc_dst; int /*<<< orphan*/  cfc_src; scalar_t__ cfd_end_offset; scalar_t__ cfd_start_offset; } ;
struct cfil_info {int /*<<< orphan*/  cfi_first_event; int /*<<< orphan*/  cfi_hash_entry; struct cfil_entry* cfi_entries; } ;
struct cfe_buf {scalar_t__ cfe_peeked; } ;
struct cfil_entry {int /*<<< orphan*/  cfe_flags; struct content_filter* cfe_filter; TYPE_1__* cfe_cfil_info; struct cfe_buf cfe_rcv; struct cfe_buf cfe_snd; } ;
typedef  scalar_t__ errno_t ;
struct TYPE_6__ {int /*<<< orphan*/  cfs_data_event_fail; int /*<<< orphan*/  cfs_data_event_flow_control; int /*<<< orphan*/  cfs_data_event_ok; } ;
struct TYPE_4__ {int /*<<< orphan*/  cfi_sock_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFEF_FLOW_CONTROLLED ; 
 int CFF_FLOW_CONTROLLED ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  CFI_ADD_TIME_LOG (struct cfil_info*,struct timeval*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFM_OP_DATA_IN ; 
 int /*<<< orphan*/  CFM_OP_DATA_OUT ; 
 int /*<<< orphan*/  CFM_TYPE_EVENT ; 
 int /*<<< orphan*/  CTL_DATA_EOR ; 
 scalar_t__ ENOBUFS ; 
 scalar_t__ ENOMEM ; 
 int INP_IPV4 ; 
 int INP_IPV6 ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  MBUF_DONTWAIT ; 
 int /*<<< orphan*/  M_COPYM_NOOP_HDR ; 
 int /*<<< orphan*/  M_DONTWAIT ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int /*<<< orphan*/  bzero (struct cfil_msg_data_event*,size_t) ; 
 struct mbuf* cfil_data_start (struct mbuf*) ; 
 int /*<<< orphan*/  cfil_get_flow_address (int /*<<< orphan*/ ,struct inpcb*,struct in_addr*,struct in_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_get_flow_address_v6 (int /*<<< orphan*/ ,struct inpcb*,struct in6_addr**,struct in6_addr**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_lck_rw ; 
 int /*<<< orphan*/  cfil_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_lock_shared_to_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_unlock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 TYPE_3__ cfil_stats ; 
 scalar_t__ ctl_enqueuembuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_ip6_sockaddr_4_6 (int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_ip_sockaddr_4_6 (int /*<<< orphan*/ *,struct in_addr,int /*<<< orphan*/ ) ; 
 struct mbuf* m_copym_mode (struct mbuf*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ mbuf_allocpacket (int /*<<< orphan*/ ,size_t,unsigned int*,struct mbuf**) ; 
 scalar_t__ mbuf_data (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_pkthdr_setlen (struct mbuf*,size_t) ; 
 int /*<<< orphan*/  mbuf_setlen (struct mbuf*,size_t) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 

__attribute__((used)) static int
cfil_dispatch_data_event(struct socket *so, struct cfil_info *cfil_info, uint32_t kcunit, int outgoing,
						 struct mbuf *data, unsigned int copyoffset, unsigned int copylen)
{
	errno_t error = 0;
	struct mbuf *copy = NULL;
	struct mbuf *msg = NULL;
	unsigned int one = 1;
	struct cfil_msg_data_event *data_req;
	size_t hdrsize;
	struct inpcb *inp = (struct inpcb *)so->so_pcb;
	struct cfil_entry *entry;
	struct cfe_buf *entrybuf;
	struct content_filter *cfc;
	struct timeval tv;

	cfil_rw_lock_shared(&cfil_lck_rw);

	entry = &cfil_info->cfi_entries[kcunit - 1];
	if (outgoing)
		entrybuf = &entry->cfe_snd;
	else
		entrybuf = &entry->cfe_rcv;

	cfc = entry->cfe_filter;
	if (cfc == NULL)
		goto done;

	data = cfil_data_start(data);
	if (data == NULL || (data->m_flags & M_PKTHDR) == 0) {
		CFIL_LOG(LOG_ERR, "NOT PKTHDR");
		goto done;
	}

	CFIL_LOG(LOG_INFO, "so %llx kcunit %u outgoing %d",
		(uint64_t)VM_KERNEL_ADDRPERM(so), kcunit, outgoing);

	socket_lock_assert_owned(so);

	/* Would be wasteful to try */
	if (cfc->cf_flags & CFF_FLOW_CONTROLLED) {
		error = ENOBUFS;
		goto done;
	}

	/* Make a copy of the data to pass to kernel control socket */
	copy = m_copym_mode(data, copyoffset, copylen, M_DONTWAIT,
		M_COPYM_NOOP_HDR);
	if (copy == NULL) {
		CFIL_LOG(LOG_ERR, "m_copym_mode() failed");
		error = ENOMEM;
		goto done;
	}

	/* We need an mbuf packet for the message header */
	hdrsize = sizeof(struct cfil_msg_data_event);
	error = mbuf_allocpacket(MBUF_DONTWAIT, hdrsize, &one, &msg);
	if (error != 0) {
		CFIL_LOG(LOG_ERR, "mbuf_allocpacket() failed");
		m_freem(copy);
		/*
		 * ENOBUFS is to indicate flow control
		 */
		error = ENOMEM;
		goto done;
	}
	mbuf_setlen(msg, hdrsize);
	mbuf_pkthdr_setlen(msg, hdrsize + copylen);
	msg->m_next = copy;
	data_req = (struct cfil_msg_data_event *)mbuf_data(msg);
	bzero(data_req, hdrsize);
	data_req->cfd_msghdr.cfm_len = hdrsize + copylen;
	data_req->cfd_msghdr.cfm_version = 1;
	data_req->cfd_msghdr.cfm_type = CFM_TYPE_EVENT;
	data_req->cfd_msghdr.cfm_op =
		outgoing ? CFM_OP_DATA_OUT : CFM_OP_DATA_IN;
	data_req->cfd_msghdr.cfm_sock_id =
		entry->cfe_cfil_info->cfi_sock_id;
	data_req->cfd_start_offset = entrybuf->cfe_peeked;
	data_req->cfd_end_offset = entrybuf->cfe_peeked + copylen;

	/*
	 * TBD:
	 * For non connected sockets need to copy addresses from passed
	 * parameters
	 */
	if (inp->inp_vflag & INP_IPV6) {
		struct in6_addr *laddr = NULL, *faddr = NULL;
		u_int16_t lport = 0, fport = 0;

		cfil_get_flow_address_v6(cfil_info->cfi_hash_entry, inp,
								 &laddr, &faddr, &lport, &fport);
		if (outgoing) {
			fill_ip6_sockaddr_4_6(&data_req->cfc_src, laddr, lport);
			fill_ip6_sockaddr_4_6(&data_req->cfc_dst, faddr, fport);
		} else {
			fill_ip6_sockaddr_4_6(&data_req->cfc_src, faddr, fport);
			fill_ip6_sockaddr_4_6(&data_req->cfc_dst, laddr, lport);
		}
	} else if (inp->inp_vflag & INP_IPV4) {
		struct in_addr laddr = {0}, faddr = {0};
		u_int16_t lport = 0, fport = 0;

		cfil_get_flow_address(cfil_info->cfi_hash_entry, inp,
							  &laddr, &faddr, &lport, &fport);

		if (outgoing) {
			fill_ip_sockaddr_4_6(&data_req->cfc_src, laddr, lport);
			fill_ip_sockaddr_4_6(&data_req->cfc_dst, faddr, fport);
		} else {
			fill_ip_sockaddr_4_6(&data_req->cfc_src, faddr, fport);
			fill_ip_sockaddr_4_6(&data_req->cfc_dst, laddr, lport);
		}
	}

	microuptime(&tv);
	CFI_ADD_TIME_LOG(cfil_info, &tv, &cfil_info->cfi_first_event, data_req->cfd_msghdr.cfm_op);

	/* Pass the message to the content filter */
	error = ctl_enqueuembuf(entry->cfe_filter->cf_kcref,
				entry->cfe_filter->cf_kcunit,
				msg, CTL_DATA_EOR);
	if (error != 0) {
		CFIL_LOG(LOG_ERR, "ctl_enqueuembuf() failed: %d", error);
		mbuf_freem(msg);
		goto done;
	}
	entry->cfe_flags &= ~CFEF_FLOW_CONTROLLED;
	OSIncrementAtomic(&cfil_stats.cfs_data_event_ok);

#if VERDICT_DEBUG
	CFIL_LOG(LOG_ERR, "CFIL: VERDICT ACTION: so %llx sockID %llu outgoing %d: mbuf %llx copyoffset %u copylen %u",
			 (uint64_t)VM_KERNEL_ADDRPERM(so), cfil_info->cfi_sock_id, outgoing, (uint64_t)VM_KERNEL_ADDRPERM(data), copyoffset, copylen);
#endif

done:
	if (error == ENOBUFS) {
		entry->cfe_flags |= CFEF_FLOW_CONTROLLED;
		OSIncrementAtomic(
			&cfil_stats.cfs_data_event_flow_control);

		if (!cfil_rw_lock_shared_to_exclusive(&cfil_lck_rw))
			cfil_rw_lock_exclusive(&cfil_lck_rw);

		cfc->cf_flags |= CFF_FLOW_CONTROLLED;

		cfil_rw_unlock_exclusive(&cfil_lck_rw);
	} else {
		if (error != 0)
			OSIncrementAtomic(&cfil_stats.cfs_data_event_fail);

		cfil_rw_unlock_shared(&cfil_lck_rw);
	}
	return (error);
}