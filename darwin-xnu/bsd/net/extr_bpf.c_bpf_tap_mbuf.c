#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; } ;
struct bpf_packet {size_t bpfp_header_length; scalar_t__ bpfp_total_length; void* bpfp_header; void* bpfp_mbuf; int /*<<< orphan*/  bpfp_type; } ;
typedef  void* mbuf_t ;
typedef  TYPE_1__* ifnet_t ;
struct TYPE_4__ {int /*<<< orphan*/ * if_bpf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PACKET_TYPE_MBUF ; 
 int /*<<< orphan*/  bpf_tap_imp (TYPE_1__*,int /*<<< orphan*/ ,struct bpf_packet*,int) ; 

__attribute__((used)) static inline void
bpf_tap_mbuf(
	ifnet_t		ifp,
	u_int32_t	dlt,
	mbuf_t		m,
	void*		hdr,
	size_t		hlen,
	int		outbound)
{
	struct bpf_packet bpf_pkt;
	struct mbuf *m0;

	if (ifp->if_bpf == NULL) {
		/* quickly check without taking lock */
		return;
	}
	bpf_pkt.bpfp_type = BPF_PACKET_TYPE_MBUF;
	bpf_pkt.bpfp_mbuf = m;
	bpf_pkt.bpfp_total_length = 0;
	for (m0 = m; m0 != NULL; m0 = m0->m_next)
		bpf_pkt.bpfp_total_length += m0->m_len;
	bpf_pkt.bpfp_header = hdr;
	if (hdr != NULL) {
		bpf_pkt.bpfp_total_length += hlen;
		bpf_pkt.bpfp_header_length = hlen;
	} else {
		bpf_pkt.bpfp_header_length = 0;
	}
	bpf_tap_imp(ifp, dlt, &bpf_pkt, outbound);
}