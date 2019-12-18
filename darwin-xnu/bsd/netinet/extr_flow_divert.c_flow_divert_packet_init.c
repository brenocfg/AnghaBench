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
struct flow_divert_pcb {int /*<<< orphan*/  hash; } ;
struct flow_divert_packet_header {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  packet_type; } ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MBUF_DONTWAIT ; 
 int /*<<< orphan*/  MBUF_TYPE_HEADER ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int mbuf_copyback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct flow_divert_packet_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ *) ; 
 int mbuf_gethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
flow_divert_packet_init(struct flow_divert_pcb *fd_cb, uint8_t packet_type, mbuf_t *packet)
{
	struct flow_divert_packet_header	hdr;
	int					error		= 0;

	error = mbuf_gethdr(MBUF_DONTWAIT, MBUF_TYPE_HEADER, packet);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "failed to allocate the header mbuf: %d", error);
		return error;
	}

	hdr.packet_type = packet_type;
	hdr.conn_id = htonl(fd_cb->hash);

	/* Lay down the header */
	error = mbuf_copyback(*packet, 0, sizeof(hdr), &hdr, MBUF_DONTWAIT);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "mbuf_copyback(hdr) failed: %d", error);
		mbuf_freem(*packet);
		*packet = NULL;
		return error;
	}

	return 0;
}