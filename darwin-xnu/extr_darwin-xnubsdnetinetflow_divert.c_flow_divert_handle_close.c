#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct flow_divert_pcb {TYPE_1__* so; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  how ;
typedef  int /*<<< orphan*/  close_error ;
struct TYPE_6__ {void* so_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDLOCK (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int) ; 
 int /*<<< orphan*/  FDUNLOCK (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_ERROR_CODE ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_HOW ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int SHUT_RD ; 
 int SHUT_RDWR ; 
 int SHUT_WR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  flow_divert_disconnect_socket (TYPE_1__*) ; 
 int flow_divert_packet_get_tlv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int flow_divert_tunnel_how_closed (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  flow_divert_update_closed_state (struct flow_divert_pcb*,int,int /*<<< orphan*/ ) ; 
 void* ntohl (int) ; 
 int /*<<< orphan*/  socantrcvmore (TYPE_1__*) ; 
 int /*<<< orphan*/  socantsendmore (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flow_divert_handle_close(struct flow_divert_pcb *fd_cb, mbuf_t packet, int offset)
{
	uint32_t	close_error;
	int			error			= 0;
	int			how;

	error = flow_divert_packet_get_tlv(packet, offset, FLOW_DIVERT_TLV_ERROR_CODE, sizeof(close_error), &close_error, NULL);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "failed to get the close error: %d", error);
		return;
	}

	error = flow_divert_packet_get_tlv(packet, offset, FLOW_DIVERT_TLV_HOW, sizeof(how), &how, NULL);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "failed to get the close how flag: %d", error);
		return;
	}

	how = ntohl(how);

	FDLOG(LOG_INFO, fd_cb, "close received, how = %d", how);

	FDLOCK(fd_cb);
	if (fd_cb->so != NULL) {
		socket_lock(fd_cb->so, 0);

		fd_cb->so->so_error = ntohl(close_error);

		flow_divert_update_closed_state(fd_cb, how, TRUE);
		
		how = flow_divert_tunnel_how_closed(fd_cb);
		if (how == SHUT_RDWR) {
			flow_divert_disconnect_socket(fd_cb->so);
		} else if (how == SHUT_RD) {
			socantrcvmore(fd_cb->so);
		} else if (how == SHUT_WR) {
			socantsendmore(fd_cb->so);
		}

		socket_unlock(fd_cb->so, 0);
	}
	FDUNLOCK(fd_cb);
}