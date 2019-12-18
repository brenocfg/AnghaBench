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
struct bpf_packet {scalar_t__ bpfp_header_length; int bpfp_type; int /*<<< orphan*/  bpfp_mbuf; int /*<<< orphan*/  bpfp_header; } ;

/* Variables and functions */
#define  BPF_PACKET_TYPE_MBUF 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  bpf_mcopy (int /*<<< orphan*/ ,void*,size_t) ; 
 size_t min (size_t,scalar_t__) ; 

__attribute__((used)) static void
copy_bpf_packet(struct bpf_packet * pkt, void * dst, size_t len)
{
	/* copy the optional header */
	if (pkt->bpfp_header_length != 0) {
		size_t	count = min(len, pkt->bpfp_header_length);
		bcopy(pkt->bpfp_header, dst, count);
		len -= count;
		dst += count;
	}
	if (len == 0) {
		/* nothing past the header */
		return;
	}
	/* copy the packet */
	switch (pkt->bpfp_type) {
	case BPF_PACKET_TYPE_MBUF:
		bpf_mcopy(pkt->bpfp_mbuf, dst, len);
		break;
	default:
		break;
	}
}