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
struct sockaddr {int dummy; } ;
struct flow_divert_pcb {size_t bytes_sent; } ;
typedef  int /*<<< orphan*/ * mbuf_t ;
typedef  int errno_t ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int) ; 
 int /*<<< orphan*/  FLOW_DIVERT_PKT_DATA ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  flow_divert_add_data_statistics (struct flow_divert_pcb*,size_t,int /*<<< orphan*/ ) ; 
 int flow_divert_append_target_endpoint_tlv (int /*<<< orphan*/ *,struct sockaddr*) ; 
 int flow_divert_packet_init (struct flow_divert_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int flow_divert_send_packet (struct flow_divert_pcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * m_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_pkthdr_adjustlen (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mbuf_setnext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static errno_t
flow_divert_send_data_packet(struct flow_divert_pcb *fd_cb, mbuf_t data, size_t data_len, struct sockaddr *toaddr, Boolean force)
{
	mbuf_t	packet;
	mbuf_t	last;
	int		error	= 0;

	error = flow_divert_packet_init(fd_cb, FLOW_DIVERT_PKT_DATA, &packet);
	if (error) {
		FDLOG(LOG_ERR, fd_cb, "flow_divert_packet_init failed: %d", error);
		return error;
	}

	if (toaddr != NULL) {
		error = flow_divert_append_target_endpoint_tlv(packet, toaddr);
		if (error) {
			FDLOG(LOG_ERR, fd_cb, "flow_divert_append_target_endpoint_tlv() failed: %d", error);
			return error;
		}
	}

	if (data_len > 0 && data != NULL) {
		last = m_last(packet);
		mbuf_setnext(last, data);
		mbuf_pkthdr_adjustlen(packet, data_len);
	}
	error = flow_divert_send_packet(fd_cb, packet, force);

	if (error) {
		mbuf_setnext(last, NULL);
		mbuf_freem(packet);
	} else {
		fd_cb->bytes_sent += data_len;
		flow_divert_add_data_statistics(fd_cb, data_len, TRUE);
	}

	return error;
}