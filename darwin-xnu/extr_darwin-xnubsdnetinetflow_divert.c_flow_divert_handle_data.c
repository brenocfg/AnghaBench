#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct flow_divert_pcb {size_t bytes_received; TYPE_3__* so; int /*<<< orphan*/  sb_size; struct sockaddr* remote_address; } ;
typedef  int /*<<< orphan*/  remote_address ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_13__ {int /*<<< orphan*/  sb_cc; } ;
struct TYPE_12__ {int so_state; TYPE_6__ so_rcv; TYPE_2__* so_proto; } ;
struct TYPE_11__ {TYPE_1__* pr_domain; } ;
struct TYPE_10__ {int /*<<< orphan*/  dom_family; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FDLOCK (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int) ; 
 int /*<<< orphan*/  FDLOG0 (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*) ; 
 int /*<<< orphan*/  FDUNLOCK (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FLOW_DIVERT_TLV_REMOTE_ADDR ; 
 int /*<<< orphan*/  FREE (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  MBUF_DONTWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SOCK_TYPE (TYPE_3__*) ; 
 int SS_CANTRCVMORE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  flow_divert_add_data_statistics (struct flow_divert_pcb*,size_t,scalar_t__) ; 
 scalar_t__ flow_divert_check_no_cellular (struct flow_divert_pcb*) ; 
 scalar_t__ flow_divert_check_no_expensive (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  flow_divert_disconnect_socket (TYPE_3__*) ; 
 int flow_divert_dup_addr (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr**) ; 
 int /*<<< orphan*/ * flow_divert_get_control_mbuf (struct flow_divert_pcb*) ; 
 scalar_t__ flow_divert_is_sockaddr_valid (struct sockaddr*) ; 
 int flow_divert_packet_get_tlv (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int,struct sockaddr_storage*,int*) ; 
 int /*<<< orphan*/  flow_divert_send_close (struct flow_divert_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_divert_update_closed_state (struct flow_divert_pcb*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ *) ; 
 size_t mbuf_pkthdr_len (int /*<<< orphan*/ *) ; 
 int mbuf_split (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sbappendaddr (TYPE_6__*,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sbappendstream (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_lock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorwakeup (TYPE_3__*) ; 

__attribute__((used)) static void
flow_divert_handle_data(struct flow_divert_pcb *fd_cb, mbuf_t packet, size_t offset)
{
	FDLOCK(fd_cb);
	if (fd_cb->so != NULL) {
		int		error		= 0;
		mbuf_t	data		= NULL;
		size_t	data_size;
		struct sockaddr_storage remote_address;
		boolean_t got_remote_sa = FALSE;

		socket_lock(fd_cb->so, 0);

		if (SOCK_TYPE(fd_cb->so) == SOCK_DGRAM) {
			uint32_t val_size = 0;

			/* check if we got remote address with data */
			memset(&remote_address, 0, sizeof(remote_address));
			error = flow_divert_packet_get_tlv(packet, offset, FLOW_DIVERT_TLV_REMOTE_ADDR, sizeof(remote_address), &remote_address, &val_size);
			if (error || val_size > sizeof(remote_address)) {
				FDLOG0(LOG_INFO, fd_cb, "No remote address provided");
				error = 0;
			} else {
				/* validate the address */
				if (flow_divert_is_sockaddr_valid((struct sockaddr *)&remote_address)) {
					got_remote_sa = TRUE;
				}
				offset += (sizeof(uint8_t) + sizeof(uint32_t) + val_size);
			}
		}

		data_size = (mbuf_pkthdr_len(packet) - offset);

		FDLOG(LOG_DEBUG, fd_cb, "received %lu bytes of data", data_size);

		error = mbuf_split(packet, offset, MBUF_DONTWAIT, &data);
		if (error || data == NULL) {
			FDLOG(LOG_ERR, fd_cb, "mbuf_split failed: %d", error);
		} else {
			if (flow_divert_check_no_cellular(fd_cb) || 
			    flow_divert_check_no_expensive(fd_cb))
			{
				flow_divert_update_closed_state(fd_cb, SHUT_RDWR, TRUE);
				flow_divert_send_close(fd_cb, SHUT_RDWR);
				flow_divert_disconnect_socket(fd_cb->so);
			} else if (!(fd_cb->so->so_state & SS_CANTRCVMORE)) {
				if (SOCK_TYPE(fd_cb->so) == SOCK_STREAM) {
					if (sbappendstream(&fd_cb->so->so_rcv, data)) {
						fd_cb->bytes_received += data_size;
						flow_divert_add_data_statistics(fd_cb, data_size, FALSE);
						fd_cb->sb_size = fd_cb->so->so_rcv.sb_cc;
						sorwakeup(fd_cb->so);
						data = NULL;
					} else {
						FDLOG0(LOG_ERR, fd_cb, "received data, but appendstream failed");
					}
				} else if (SOCK_TYPE(fd_cb->so) == SOCK_DGRAM) {
					struct sockaddr *append_sa;
					mbuf_t mctl;

					if (got_remote_sa == TRUE) {
						error = flow_divert_dup_addr(fd_cb->so->so_proto->pr_domain->dom_family,
								(struct sockaddr *)&remote_address, &append_sa);
					} else {
						error = flow_divert_dup_addr(fd_cb->so->so_proto->pr_domain->dom_family,
								fd_cb->remote_address, &append_sa);
					}
					if (error) {
						FDLOG0(LOG_ERR, fd_cb, "failed to dup the socket address.");
					}

					mctl = flow_divert_get_control_mbuf(fd_cb);
					if (sbappendaddr(&fd_cb->so->so_rcv, append_sa, data, mctl, NULL)) {
						fd_cb->bytes_received += data_size;
						flow_divert_add_data_statistics(fd_cb, data_size, FALSE);
						fd_cb->sb_size = fd_cb->so->so_rcv.sb_cc;
						sorwakeup(fd_cb->so);
						data = NULL;
					} else {
						FDLOG0(LOG_ERR, fd_cb, "received data, but sbappendaddr failed");
					}
					if (!error) {
						FREE(append_sa, M_TEMP);
					}
				}
			}
		}
		socket_unlock(fd_cb->so, 0);

		if (data != NULL) {
			mbuf_freem(data);
		}
	}
	FDUNLOCK(fd_cb);
}