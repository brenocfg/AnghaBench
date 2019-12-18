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
typedef  int uint16_t ;
struct bpf_packet {int dummy; } ;

/* Variables and functions */
 int bpf_copydata (struct bpf_packet*,int,int const,char*) ; 
 int get_esp_trunc_len (struct bpf_packet*,int,int const) ; 
 int get_isakmp_trunc_len (struct bpf_packet*,int,int const) ; 

__attribute__((used)) static uint16_t
get_isakmp_natt_trunc_len(struct bpf_packet *pkt, uint16_t off,
    const uint16_t remaining_caplen)
{
	int err = 0;
	uint16_t trunc_len = 0;
	char payload[remaining_caplen];

	err = bpf_copydata(pkt, off, remaining_caplen, payload);
	if (err != 0)
		return (remaining_caplen);
	/*
	 * They are three cases:
	 * - IKE: payload start with 4 bytes header set to zero before ISAKMP header
	 * - keep alive: 1 byte payload
	 * - otherwise it's ESP
	 */
	if (remaining_caplen >= 4 &&
		payload[0] == 0 && payload[1] == 0 &&
		payload[2] == 0 && payload[3] == 0) {
		trunc_len = 4 + get_isakmp_trunc_len(pkt, off + 4, remaining_caplen - 4);
	} else if (remaining_caplen == 1) {
		trunc_len = 1;
	} else {
		trunc_len = get_esp_trunc_len(pkt, off, remaining_caplen);
	}

	if (trunc_len > remaining_caplen)
		return (remaining_caplen);

	return (trunc_len);

}