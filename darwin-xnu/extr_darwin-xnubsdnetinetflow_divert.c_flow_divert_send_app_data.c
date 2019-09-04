#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct flow_divert_pcb {size_t send_window; TYPE_5__* so; } ;
typedef  int /*<<< orphan*/ * mbuf_t ;
struct TYPE_6__ {int /*<<< orphan*/  sb_cc; } ;
struct TYPE_7__ {TYPE_1__ so_snd; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int,...) ; 
 size_t FLOW_DIVERT_CHUNK_SIZE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MBUF_DONTWAIT ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SOCK_TYPE (TYPE_5__*) ; 
 int flow_divert_send_data_packet (struct flow_divert_pcb*,int /*<<< orphan*/ *,size_t,struct sockaddr*,int /*<<< orphan*/ ) ; 
 size_t mbuf_pkthdr_len (int /*<<< orphan*/ *) ; 
 int mbuf_split (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sbappendaddr (TYPE_1__*,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sbappendrecord (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbappendstream (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int sbspace (TYPE_1__*) ; 

__attribute__((used)) static int
flow_divert_send_app_data(struct flow_divert_pcb *fd_cb, mbuf_t data, struct sockaddr *toaddr)
{
	size_t	to_send		= mbuf_pkthdr_len(data);
	int	error		= 0;

	if (to_send > fd_cb->send_window) {
		to_send = fd_cb->send_window;
	}

	if (fd_cb->so->so_snd.sb_cc > 0) {
		to_send = 0;	/* If the send buffer is non-empty, then we can't send anything */
	}

	if (SOCK_TYPE(fd_cb->so) == SOCK_STREAM) {
		size_t	sent		= 0;
		mbuf_t	remaining_data	= data;
		mbuf_t	pkt_data	= NULL;
		while (sent < to_send && remaining_data != NULL) {
			size_t	pkt_data_len;

			pkt_data = remaining_data;

			if ((to_send - sent) > FLOW_DIVERT_CHUNK_SIZE) {
				pkt_data_len = FLOW_DIVERT_CHUNK_SIZE;
			} else {
				pkt_data_len = to_send - sent;
			}

			if (pkt_data_len < mbuf_pkthdr_len(pkt_data)) {
				error = mbuf_split(pkt_data, pkt_data_len, MBUF_DONTWAIT, &remaining_data);
				if (error) {
					FDLOG(LOG_ERR, fd_cb, "mbuf_split failed: %d", error);
					pkt_data = NULL;
					break;
				}
			} else {
				remaining_data = NULL;
			}

			error = flow_divert_send_data_packet(fd_cb, pkt_data, pkt_data_len, NULL, FALSE);

			if (error) {
				break;
			}

			pkt_data = NULL;
			sent += pkt_data_len;
		}

		fd_cb->send_window -= sent;

		error = 0;

		if (pkt_data != NULL) {
			if (sbspace(&fd_cb->so->so_snd) > 0) {
				if (!sbappendstream(&fd_cb->so->so_snd, pkt_data)) {
					FDLOG(LOG_ERR, fd_cb, "sbappendstream failed with pkt_data, send buffer size = %u, send_window = %u\n",
							fd_cb->so->so_snd.sb_cc, fd_cb->send_window);
				}
			} else {
				error = ENOBUFS;
			}
		}

		if (remaining_data != NULL) {
			if (sbspace(&fd_cb->so->so_snd) > 0) {
				if (!sbappendstream(&fd_cb->so->so_snd, remaining_data)) {
					FDLOG(LOG_ERR, fd_cb, "sbappendstream failed with remaining_data, send buffer size = %u, send_window = %u\n",
							fd_cb->so->so_snd.sb_cc, fd_cb->send_window);
				}
			} else {
				error = ENOBUFS;
			}
		}
	} else if (SOCK_TYPE(fd_cb->so) == SOCK_DGRAM) {
		if (to_send || mbuf_pkthdr_len(data) == 0) {
			error = flow_divert_send_data_packet(fd_cb, data, to_send, toaddr, FALSE);
			if (error) {
				FDLOG(LOG_ERR, fd_cb, "flow_divert_send_data_packet failed. send data size = %lu", to_send);
			} else {
				fd_cb->send_window -= to_send;
			}
		} else {
			/* buffer it */
			if (sbspace(&fd_cb->so->so_snd) >= (int)mbuf_pkthdr_len(data)) {
				if (toaddr != NULL) {
					if (!sbappendaddr(&fd_cb->so->so_snd, toaddr, data, NULL, &error)) {
						FDLOG(LOG_ERR, fd_cb,
							"sbappendaddr failed. send buffer size = %u, send_window = %u, error = %d\n",
							fd_cb->so->so_snd.sb_cc, fd_cb->send_window, error);
					}
				} else {
					if (!sbappendrecord(&fd_cb->so->so_snd, data)) {
						FDLOG(LOG_ERR, fd_cb,
							"sbappendrecord failed. send buffer size = %u, send_window = %u, error = %d\n",
							fd_cb->so->so_snd.sb_cc, fd_cb->send_window, error);
					}
				}
			} else {
				error = ENOBUFS;
			}
		}
	}

	return error;
}