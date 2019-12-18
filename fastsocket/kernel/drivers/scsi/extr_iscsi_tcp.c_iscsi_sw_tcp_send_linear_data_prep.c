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
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_segment; TYPE_1__* hdr; } ;
struct hash_desc {int dummy; } ;
struct iscsi_sw_tcp_conn {TYPE_2__ out; struct hash_desc tx_hash; } ;
struct iscsi_conn {scalar_t__ datadgst_en; struct iscsi_tcp_conn* dd_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dlength; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SW_TCP_DBG (struct iscsi_conn*,char*,size_t,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ iscsi_padded (unsigned int) ; 
 int /*<<< orphan*/  iscsi_segment_init_linear (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *,struct hash_desc*) ; 
 unsigned int ntoh24 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iscsi_sw_tcp_send_linear_data_prep(struct iscsi_conn *conn, void *data,
				   size_t len)
{
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	struct hash_desc *tx_hash = NULL;
	unsigned int hdr_spec_len;

	ISCSI_SW_TCP_DBG(conn, "datalen=%zd %s\n", len, conn->datadgst_en ?
			 "digest enabled" : "digest disabled");

	/* Make sure the datalen matches what the caller
	   said he would send. */
	hdr_spec_len = ntoh24(tcp_sw_conn->out.hdr->dlength);
	WARN_ON(iscsi_padded(len) != iscsi_padded(hdr_spec_len));

	if (conn->datadgst_en)
		tx_hash = &tcp_sw_conn->tx_hash;

	iscsi_segment_init_linear(&tcp_sw_conn->out.data_segment,
				data, len, NULL, tx_hash);
}