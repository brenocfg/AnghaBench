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
struct TYPE_2__ {int /*<<< orphan*/  datalen; int /*<<< orphan*/  hdr; } ;
struct iscsi_tcp_conn {TYPE_1__ in; struct iscsi_conn* iscsi_conn; } ;
struct iscsi_segment {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ISCSI_ERR_DATA_DGST ; 
 int iscsi_complete_pdu (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_tcp_dgst_verify (struct iscsi_tcp_conn*,struct iscsi_segment*) ; 
 int /*<<< orphan*/  iscsi_tcp_hdr_recv_prep (struct iscsi_tcp_conn*) ; 

__attribute__((used)) static int
iscsi_tcp_data_recv_done(struct iscsi_tcp_conn *tcp_conn,
			 struct iscsi_segment *segment)
{
	struct iscsi_conn *conn = tcp_conn->iscsi_conn;
	int rc = 0;

	if (!iscsi_tcp_dgst_verify(tcp_conn, segment))
		return ISCSI_ERR_DATA_DGST;

	rc = iscsi_complete_pdu(conn, tcp_conn->in.hdr,
			conn->data, tcp_conn->in.datalen);
	if (rc)
		return rc;

	iscsi_tcp_hdr_recv_prep(tcp_conn);
	return 0;
}