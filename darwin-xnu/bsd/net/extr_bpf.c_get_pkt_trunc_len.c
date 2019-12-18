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
typedef  int uint32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pktap_header {int pth_frame_pre_length; int pth_length; scalar_t__ pth_protocol_family; scalar_t__ pth_iftype; } ;
struct ether_header {int dummy; } ;
struct bpf_packet {int bpfp_header_length; scalar_t__ bpfp_header; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  BPF_MIN_PKT_SIZE ; 
 scalar_t__ IFT_ETHER ; 
 int MIN (int,int) ; 
 int get_ether_trunc_len (struct bpf_packet*,int /*<<< orphan*/ ,int) ; 
 int get_ip6_trunc_len (struct bpf_packet*,int,int) ; 
 int get_ip_trunc_len (struct bpf_packet*,int,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
get_pkt_trunc_len(u_char *p, u_int len)
{
	struct bpf_packet *pkt = (struct bpf_packet *)(void *) p;
	struct pktap_header *pktap = (struct pktap_header *) (pkt->bpfp_header);
	uint32_t out_pkt_len = 0, tlen = 0;
	/*
	 * pktap->pth_frame_pre_length is L2 header length and accounts
	 * for both pre and pre_adjust.
	 * pktap->pth_length is sizeof(pktap_header) (excl the pre/pre_adjust)
	 * pkt->bpfp_header_length is (pktap->pth_length + pre_adjust)
	 * pre is the offset to the L3 header after the bpfp_header, or length
	 * of L2 header after bpfp_header, if present.
	*/
	uint32_t pre = pktap->pth_frame_pre_length -
	    (pkt->bpfp_header_length - pktap->pth_length);

	/* Length of the input packet starting from  L3 header */
	uint32_t in_pkt_len = len - pkt->bpfp_header_length - pre;
	if (pktap->pth_protocol_family == AF_INET ||
	    pktap->pth_protocol_family == AF_INET6) {
		/* Contains L2 header */
		if (pre > 0) {
			if (pre < sizeof(struct ether_header))
				goto too_short;

			out_pkt_len = get_ether_trunc_len(pkt, 0, in_pkt_len);
		} else if (pre == 0) {
			if (pktap->pth_protocol_family == AF_INET) {
				out_pkt_len = get_ip_trunc_len(pkt, pre, in_pkt_len);
			} else if (pktap->pth_protocol_family == AF_INET6) {
				out_pkt_len = get_ip6_trunc_len(pkt, pre, in_pkt_len);
			}
		} else {
			/* Ideally pre should be >= 0. This is an exception */
			out_pkt_len = min(BPF_MIN_PKT_SIZE, in_pkt_len);
		}
	} else {
		if (pktap->pth_iftype == IFT_ETHER) {
			if (in_pkt_len < sizeof(struct ether_header)) {
				goto too_short;
			}
			/* At most include the Ethernet header and 16 bytes */
			out_pkt_len = MIN(sizeof(struct ether_header) + 16,
			    in_pkt_len);
		} else {
			/*
			 * For unknown protocols include at most 16 bytes
			 */
			out_pkt_len = MIN(16, in_pkt_len);
		}
	}
done:
	tlen = pkt->bpfp_header_length + out_pkt_len + pre;
	return (tlen);
too_short:
	out_pkt_len = in_pkt_len;
	goto done;
}