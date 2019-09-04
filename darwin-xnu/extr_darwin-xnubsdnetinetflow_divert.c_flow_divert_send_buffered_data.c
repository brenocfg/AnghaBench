#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct flow_divert_pcb {size_t send_window; TYPE_2__* so; } ;
typedef  TYPE_1__* mbuf_t ;
struct TYPE_14__ {size_t sb_cc; TYPE_1__* sb_mb; } ;
struct TYPE_13__ {TYPE_3__ so_snd; } ;
struct TYPE_12__ {scalar_t__ m_type; struct TYPE_12__* m_nextpkt; struct TYPE_12__* m_next; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,size_t) ; 
 int /*<<< orphan*/  FDLOG0 (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*) ; 
 size_t FLOW_DIVERT_CHUNK_SIZE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MBUF_DONTWAIT ; 
 scalar_t__ MT_DATA ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SOCK_TYPE (TYPE_2__*) ; 
 struct sockaddr* flow_divert_get_buffered_target_address (TYPE_1__*) ; 
 int flow_divert_send_data_packet (struct flow_divert_pcb*,TYPE_1__*,size_t,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int mbuf_copym (TYPE_1__*,size_t,size_t,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  mbuf_freem (TYPE_1__*) ; 
 size_t mbuf_pkthdr_len (TYPE_1__*) ; 
 int /*<<< orphan*/  sbdrop (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  sbdroprecord (TYPE_3__*) ; 
 int /*<<< orphan*/  sowwakeup (TYPE_2__*) ; 

__attribute__((used)) static void
flow_divert_send_buffered_data(struct flow_divert_pcb *fd_cb, Boolean force)
{
	size_t	to_send;
	size_t	sent	= 0;
	int		error	= 0;
	mbuf_t	buffer;

	to_send = fd_cb->so->so_snd.sb_cc;
	buffer = fd_cb->so->so_snd.sb_mb;

	if (buffer == NULL && to_send > 0) {
		FDLOG(LOG_ERR, fd_cb, "Send buffer is NULL, but size is supposed to be %lu", to_send);
		return;
	}

	/* Ignore the send window if force is enabled */
	if (!force && (to_send > fd_cb->send_window)) {
		to_send = fd_cb->send_window;
	}

	if (SOCK_TYPE(fd_cb->so) == SOCK_STREAM) {
		while (sent < to_send) {
			mbuf_t	data;
			size_t	data_len;

			data_len = to_send - sent;
			if (data_len > FLOW_DIVERT_CHUNK_SIZE) {
				data_len = FLOW_DIVERT_CHUNK_SIZE;
			}

			error = mbuf_copym(buffer, sent, data_len, MBUF_DONTWAIT, &data);
			if (error) {
				FDLOG(LOG_ERR, fd_cb, "mbuf_copym failed: %d", error);
				break;
			}

			error = flow_divert_send_data_packet(fd_cb, data, data_len, NULL, force);
			if (error) {
				mbuf_freem(data);
				break;
			}

			sent += data_len;
		}
		sbdrop(&fd_cb->so->so_snd, sent);
		sowwakeup(fd_cb->so);
	} else if (SOCK_TYPE(fd_cb->so) == SOCK_DGRAM) {
		mbuf_t data;
		mbuf_t m;
		size_t data_len;

		while(buffer) {
			struct sockaddr *toaddr = flow_divert_get_buffered_target_address(buffer);

			m = buffer;
			if (toaddr != NULL) {
				/* look for data in the chain */
				do {
					m = m->m_next;
					if (m != NULL && m->m_type == MT_DATA) {
						break;
					}
				} while(m);
				if (m == NULL) {
					/* unexpected */
					FDLOG0(LOG_ERR, fd_cb, "failed to find type MT_DATA in the mbuf chain.");
					goto move_on;
				}
			}
			data_len = mbuf_pkthdr_len(m);
			if (data_len > 0) {
				FDLOG(LOG_DEBUG, fd_cb, "mbuf_copym() data_len = %lu", data_len);
				error = mbuf_copym(m, 0, data_len, MBUF_DONTWAIT, &data);
				if (error) {
					FDLOG(LOG_ERR, fd_cb, "mbuf_copym failed: %d", error);
					break;
				}
			} else {
				data = NULL;
			}
			error = flow_divert_send_data_packet(fd_cb, data, data_len, toaddr, force);
			if (error) {
				mbuf_freem(data);
				break;
			}
			sent += data_len;
move_on:
			buffer = buffer->m_nextpkt;
			(void) sbdroprecord(&(fd_cb->so->so_snd));
		}
	}

	if (sent > 0) {
		FDLOG(LOG_DEBUG, fd_cb, "sent %lu bytes of buffered data", sent);
		if (fd_cb->send_window >= sent) {
			fd_cb->send_window -= sent;
		} else {
			fd_cb->send_window = 0;
		}
	}
}