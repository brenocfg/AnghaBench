#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct flow_divert_pcb {TYPE_2__* so; } ;
typedef  int /*<<< orphan*/  rbuff_space ;
typedef  int /*<<< orphan*/ * mbuf_t ;
struct TYPE_3__ {int sb_hiwat; } ;
struct TYPE_4__ {TYPE_1__ so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int) ; 
 int /*<<< orphan*/  FLOW_DIVERT_PKT_CONNECT_RESULT ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_SPACE_AVAILABLE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TRUE ; 
 int flow_divert_packet_append_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int flow_divert_packet_init (struct flow_divert_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int flow_divert_send_packet (struct flow_divert_pcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int htonl (int) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
flow_divert_send_connect_result(struct flow_divert_pcb *fd_cb)
{
	int		error	 		= 0;
	mbuf_t	packet			= NULL;
	int		rbuff_space		= 0;

	error = flow_divert_packet_init(fd_cb, FLOW_DIVERT_PKT_CONNECT_RESULT, &packet);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "failed to create a connect result packet: %d", error);
		goto done;
	}

	rbuff_space = fd_cb->so->so_rcv.sb_hiwat;
	if (rbuff_space < 0) {
		rbuff_space = 0;
	}
	rbuff_space = htonl(rbuff_space);
	error = flow_divert_packet_append_tlv(packet,
	                                      FLOW_DIVERT_TLV_SPACE_AVAILABLE,
	                                      sizeof(rbuff_space),
	                                      &rbuff_space);
	if (error) {
		goto done;
	}

	error = flow_divert_send_packet(fd_cb, packet, TRUE);
	if (error) {
		goto done;
	}

done:
	if (error && packet != NULL) {
		mbuf_freem(packet);
	}

	return error;
}