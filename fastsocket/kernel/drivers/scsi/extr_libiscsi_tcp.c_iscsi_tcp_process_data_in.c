#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct iscsi_hdr* hdr; } ;
struct iscsi_tcp_conn {TYPE_1__ in; struct iscsi_conn* iscsi_conn; } ;
struct iscsi_segment {int dummy; } ;
struct iscsi_hdr {int flags; } ;
struct iscsi_conn {int dummy; } ;

/* Variables and functions */
 int ISCSI_ERR_DATA_DGST ; 
 int ISCSI_FLAG_DATA_STATUS ; 
 int iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_tcp_dgst_verify (struct iscsi_tcp_conn*,struct iscsi_segment*) ; 
 int /*<<< orphan*/  iscsi_tcp_hdr_recv_prep (struct iscsi_tcp_conn*) ; 

__attribute__((used)) static int
iscsi_tcp_process_data_in(struct iscsi_tcp_conn *tcp_conn,
			  struct iscsi_segment *segment)
{
	struct iscsi_conn *conn = tcp_conn->iscsi_conn;
	struct iscsi_hdr *hdr = tcp_conn->in.hdr;
	int rc;

	if (!iscsi_tcp_dgst_verify(tcp_conn, segment))
		return ISCSI_ERR_DATA_DGST;

	/* check for non-exceptional status */
	if (hdr->flags & ISCSI_FLAG_DATA_STATUS) {
		rc = iscsi_complete_pdu(conn, tcp_conn->in.hdr, NULL, 0);
		if (rc)
			return rc;
	}

	iscsi_tcp_hdr_recv_prep(tcp_conn);
	return 0;
}