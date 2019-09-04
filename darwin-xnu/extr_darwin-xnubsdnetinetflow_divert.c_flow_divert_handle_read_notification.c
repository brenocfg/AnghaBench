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
typedef  int /*<<< orphan*/  uint32_t ;
struct flow_divert_pcb {int send_window; int /*<<< orphan*/ * so; } ;
typedef  int /*<<< orphan*/  read_count ;
typedef  int /*<<< orphan*/  mbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FDLOCK (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int) ; 
 int /*<<< orphan*/  FDUNLOCK (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_READ_COUNT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int flow_divert_packet_get_tlv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flow_divert_send_buffered_data (struct flow_divert_pcb*,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flow_divert_handle_read_notification(struct flow_divert_pcb *fd_cb, mbuf_t packet, int offset)
{
	uint32_t	read_count;
	int		error			= 0;

	error = flow_divert_packet_get_tlv(packet, offset, FLOW_DIVERT_TLV_READ_COUNT, sizeof(read_count), &read_count, NULL);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "failed to get the read count: %d", error);
		return;
	}

	FDLOG(LOG_DEBUG, fd_cb, "received a read notification for %u bytes", ntohl(read_count));

	FDLOCK(fd_cb);
	if (fd_cb->so != NULL) {
		socket_lock(fd_cb->so, 0);
		fd_cb->send_window += ntohl(read_count);
		flow_divert_send_buffered_data(fd_cb, FALSE);
		socket_unlock(fd_cb->so, 0);
	}
	FDUNLOCK(fd_cb);
}