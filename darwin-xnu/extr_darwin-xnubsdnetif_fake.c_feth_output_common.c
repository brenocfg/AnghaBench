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
struct TYPE_2__ {int csum_data; int csum_flags; int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ether_header {int dummy; } ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int iff_flags_t ;

/* Variables and functions */
 int CSUM_DATA_VALID ; 
 int CSUM_IP_CHECKED ; 
 int CSUM_IP_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 int /*<<< orphan*/  DLT_EN10MB ; 
 int ETHER_HDR_LEN ; 
 int IFF_FLAGS_HWCSUM ; 
 int /*<<< orphan*/  bpf_tap_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,void*,int) ; 
 int /*<<< orphan*/  bpf_tap_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feth_enqueue_input (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  ifnet_stat_increment_out (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mbuf_data (struct mbuf*) ; 
 scalar_t__ mbuf_len (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_pkthdr_adjustlen (struct mbuf*,int) ; 
 int /*<<< orphan*/  mbuf_pkthdr_setheader (struct mbuf*,void*) ; 
 int /*<<< orphan*/  mbuf_pkthdr_setrcvif (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_setdata (struct mbuf*,char*,scalar_t__) ; 

__attribute__((used)) static void
feth_output_common(ifnet_t ifp, struct mbuf * m, ifnet_t peer,
		   iff_flags_t flags)
{
	void *		frame_header;

	frame_header = mbuf_data(m);
	if ((flags & IFF_FLAGS_HWCSUM) != 0) {
		m->m_pkthdr.csum_data = 0xffff;
		m->m_pkthdr.csum_flags =
			CSUM_DATA_VALID | CSUM_PSEUDO_HDR |
			CSUM_IP_CHECKED | CSUM_IP_VALID;
	}

	(void)ifnet_stat_increment_out(ifp, 1, m->m_pkthdr.len, 0);
	bpf_tap_out(ifp, DLT_EN10MB, m, NULL, 0);

	(void)mbuf_pkthdr_setrcvif(m, peer);
	mbuf_pkthdr_setheader(m, frame_header);
	mbuf_pkthdr_adjustlen(m, - ETHER_HDR_LEN);
	(void)mbuf_setdata(m, (char *)mbuf_data(m) + ETHER_HDR_LEN,
			   mbuf_len(m) - ETHER_HDR_LEN);
	bpf_tap_in(peer, DLT_EN10MB, m, frame_header,
		   sizeof(struct ether_header));
	feth_enqueue_input(peer, m);
}