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
typedef  int /*<<< orphan*/  zero ;
typedef  int uint32_t ;
struct flow_divert_pcb {int dummy; } ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int /*<<< orphan*/  how ;

/* Variables and functions */
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int) ; 
 int /*<<< orphan*/  FLOW_DIVERT_PKT_CLOSE ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_ERROR_CODE ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_HOW ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TRUE ; 
 int flow_divert_packet_append_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int flow_divert_packet_init (struct flow_divert_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int flow_divert_send_packet (struct flow_divert_pcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int htonl (int) ; 
 int /*<<< orphan*/  mbuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
flow_divert_send_close(struct flow_divert_pcb *fd_cb, int how)
{
	int		error	= 0;
	mbuf_t	packet	= NULL;
	uint32_t	zero	= 0;

	error = flow_divert_packet_init(fd_cb, FLOW_DIVERT_PKT_CLOSE, &packet);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "failed to create a close packet: %d", error);
		goto done;
	}

	error = flow_divert_packet_append_tlv(packet, FLOW_DIVERT_TLV_ERROR_CODE, sizeof(zero), &zero);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "failed to add the error code TLV: %d", error);
		goto done;
	}

	how = htonl(how);
	error = flow_divert_packet_append_tlv(packet, FLOW_DIVERT_TLV_HOW, sizeof(how), &how);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "failed to add the how flag: %d", error);
		goto done;
	}

	error = flow_divert_send_packet(fd_cb, packet, TRUE);
	if (error) {
		goto done;
	}

done:
	if (error && packet != NULL) {
		mbuf_free(packet);
	}

	return error;
}