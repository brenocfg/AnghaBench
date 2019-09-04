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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  net_length ;
typedef  int /*<<< orphan*/  mbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FDLOG0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MBUF_DONTWAIT ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int mbuf_copyback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_pkthdr_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nil_pcb ; 

__attribute__((used)) static int
flow_divert_packet_append_tlv(mbuf_t packet, uint8_t type, uint32_t length, const void *value)
{
	uint32_t	net_length	= htonl(length);
	int			error		= 0;

	error = mbuf_copyback(packet, mbuf_pkthdr_len(packet), sizeof(type), &type, MBUF_DONTWAIT);
	if (error) {
		FDLOG(LOG_ERR, &nil_pcb, "failed to append the type (%d)", type);
		return error;
	}

	error = mbuf_copyback(packet, mbuf_pkthdr_len(packet), sizeof(net_length), &net_length, MBUF_DONTWAIT);
	if (error) {
		FDLOG(LOG_ERR, &nil_pcb, "failed to append the length (%u)", length);
		return error;
	}

	error = mbuf_copyback(packet, mbuf_pkthdr_len(packet), length, value, MBUF_DONTWAIT);
	if (error) {
		FDLOG0(LOG_ERR, &nil_pcb, "failed to append the value");
		return error;
	}

	return error;
}