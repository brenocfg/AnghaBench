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
struct bpf_packet {scalar_t__ bpfp_type; int /*<<< orphan*/  bpfp_mbuf; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 scalar_t__ BPF_PACKET_TYPE_MBUF ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  mbuf_copydata (int /*<<< orphan*/ ,size_t,size_t,void*) ; 

__attribute__((used)) static errno_t
bpf_copydata(struct bpf_packet *pkt, size_t off, size_t len, void* out_data)
{
	errno_t err = 0;
	if (pkt->bpfp_type == BPF_PACKET_TYPE_MBUF) {
		err = mbuf_copydata(pkt->bpfp_mbuf, off, len, out_data);
	} else {
		err = EINVAL;
	}

	return (err);
}