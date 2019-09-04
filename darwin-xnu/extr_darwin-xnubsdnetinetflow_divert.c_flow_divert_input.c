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
struct flow_divert_pcb {int dummy; } ;
struct flow_divert_packet_header {scalar_t__ conn_id; int packet_type; } ;
struct flow_divert_group {int /*<<< orphan*/  ctl_unit; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int,...) ; 
 int /*<<< orphan*/  FDRELEASE (struct flow_divert_pcb*) ; 
 int FD_CTL_RCVBUFF_SIZE ; 
#define  FLOW_DIVERT_PKT_APP_MAP_CREATE 134 
#define  FLOW_DIVERT_PKT_CLOSE 133 
#define  FLOW_DIVERT_PKT_CONNECT_RESULT 132 
#define  FLOW_DIVERT_PKT_DATA 131 
#define  FLOW_DIVERT_PKT_GROUP_INIT 130 
#define  FLOW_DIVERT_PKT_PROPERTIES_UPDATE 129 
#define  FLOW_DIVERT_PKT_READ_NOTIFY 128 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  flow_divert_handle_app_map_create (struct flow_divert_group*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flow_divert_handle_close (struct flow_divert_pcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flow_divert_handle_connect_result (struct flow_divert_pcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flow_divert_handle_data (struct flow_divert_pcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flow_divert_handle_group_init (struct flow_divert_group*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flow_divert_handle_properties_update (struct flow_divert_pcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flow_divert_handle_read_notification (struct flow_divert_pcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flow_divert_packet_type2str (int) ; 
 struct flow_divert_pcb* flow_divert_pcb_lookup (scalar_t__,struct flow_divert_group*) ; 
 int mbuf_copydata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct flow_divert_packet_header*) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ ) ; 
 int mbuf_pkthdr_len (int /*<<< orphan*/ ) ; 
 struct flow_divert_pcb nil_pcb ; 
 scalar_t__ ntohl (scalar_t__) ; 

__attribute__((used)) static int
flow_divert_input(mbuf_t packet, struct flow_divert_group *group)
{
	struct flow_divert_packet_header	hdr;
	int									error		= 0;
	struct flow_divert_pcb				*fd_cb;

	if (mbuf_pkthdr_len(packet) < sizeof(hdr)) {
		FDLOG(LOG_ERR, &nil_pcb, "got a bad packet, length (%lu) < sizeof hdr (%lu)", mbuf_pkthdr_len(packet), sizeof(hdr));
		error = EINVAL;
		goto done;
	}

	if (mbuf_pkthdr_len(packet) > FD_CTL_RCVBUFF_SIZE) {
		FDLOG(LOG_ERR, &nil_pcb, "got a bad packet, length (%lu) > %d", mbuf_pkthdr_len(packet), FD_CTL_RCVBUFF_SIZE);
		error = EINVAL;
		goto done;
	}

	error = mbuf_copydata(packet, 0, sizeof(hdr), &hdr);
	if (error) {
		FDLOG(LOG_ERR, &nil_pcb, "mbuf_copydata failed for the header: %d", error);
		error = ENOBUFS;
		goto done;
	}

	hdr.conn_id = ntohl(hdr.conn_id);

	if (hdr.conn_id == 0) {
		switch (hdr.packet_type) {
			case FLOW_DIVERT_PKT_GROUP_INIT:
				flow_divert_handle_group_init(group, packet, sizeof(hdr));
				break;
			case FLOW_DIVERT_PKT_APP_MAP_CREATE:
				flow_divert_handle_app_map_create(group, packet, sizeof(hdr));
				break;
			default:
				FDLOG(LOG_WARNING, &nil_pcb, "got an unknown message type: %d", hdr.packet_type);
				break;
		}
		goto done;
	}

	fd_cb = flow_divert_pcb_lookup(hdr.conn_id, group);		/* This retains the PCB */
	if (fd_cb == NULL) {
		if (hdr.packet_type != FLOW_DIVERT_PKT_CLOSE && hdr.packet_type != FLOW_DIVERT_PKT_READ_NOTIFY) {
			FDLOG(LOG_NOTICE, &nil_pcb, "got a %s message from group %d for an unknown pcb: %u", flow_divert_packet_type2str(hdr.packet_type), group->ctl_unit, hdr.conn_id);
		}
		goto done;
	}

	switch (hdr.packet_type) {
		case FLOW_DIVERT_PKT_CONNECT_RESULT:
			flow_divert_handle_connect_result(fd_cb, packet, sizeof(hdr));
			break;
		case FLOW_DIVERT_PKT_CLOSE:
			flow_divert_handle_close(fd_cb, packet, sizeof(hdr));
			break;
		case FLOW_DIVERT_PKT_DATA:
			flow_divert_handle_data(fd_cb, packet, sizeof(hdr));
			break;
		case FLOW_DIVERT_PKT_READ_NOTIFY:
			flow_divert_handle_read_notification(fd_cb, packet, sizeof(hdr));
			break;
		case FLOW_DIVERT_PKT_PROPERTIES_UPDATE:
			flow_divert_handle_properties_update(fd_cb, packet, sizeof(hdr));
			break;
		default:
			FDLOG(LOG_WARNING, fd_cb, "got an unknown message type: %d", hdr.packet_type);
			break;
	}

	FDRELEASE(fd_cb);

done:
	mbuf_freem(packet);
	return error;
}