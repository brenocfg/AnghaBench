#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {scalar_t__ binary_encoded; } ;
struct TYPE_35__ {TYPE_4__* fields; TYPE_12__* rows_chunk_head; int /*<<< orphan*/  bytes; int /*<<< orphan*/  rows; TYPE_3__ qstat; scalar_t__ result_queue; } ;
typedef  TYPE_7__ proxy_resultset_t ;
struct TYPE_36__ {scalar_t__ offset; TYPE_5__* data; } ;
typedef  TYPE_8__ network_packet ;
typedef  int network_mysqld_lenenc_type ;
struct TYPE_37__ {TYPE_6__* merge_res; TYPE_2__* server; } ;
typedef  TYPE_9__ network_mysqld_con ;
struct TYPE_26__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  rows; TYPE_3__ qstat; int /*<<< orphan*/  resultset_is_needed; } ;
typedef  TYPE_10__ injection ;
typedef  int guint64 ;
typedef  scalar_t__ guint ;
struct TYPE_34__ {scalar_t__ limit; TYPE_11__* rows; } ;
struct TYPE_33__ {scalar_t__ str; } ;
struct TYPE_32__ {scalar_t__ len; } ;
struct TYPE_30__ {TYPE_1__* recv_queue; } ;
struct TYPE_29__ {scalar_t__ chunks; } ;
struct TYPE_28__ {struct TYPE_28__* next; TYPE_5__* data; } ;
struct TYPE_27__ {scalar_t__ len; } ;
typedef  TYPE_11__ GPtrArray ;
typedef  TYPE_12__ GList ;

/* Variables and functions */
#define  NETWORK_MYSQLD_LENENC_TYPE_EOF 131 
#define  NETWORK_MYSQLD_LENENC_TYPE_ERR 130 
#define  NETWORK_MYSQLD_LENENC_TYPE_INT 129 
#define  NETWORK_MYSQLD_LENENC_TYPE_NULL 128 
 int /*<<< orphan*/  g_ptr_array_add (TYPE_11__*,TYPE_11__*) ; 
 TYPE_11__* g_ptr_array_new () ; 
 TYPE_11__* g_strndup (scalar_t__,int) ; 
 int /*<<< orphan*/  network_mysqld_proto_get_lenenc_int (TYPE_8__*,int*) ; 
 int /*<<< orphan*/  network_mysqld_proto_peek_lenenc_type (TYPE_8__*,int*) ; 
 int /*<<< orphan*/  network_mysqld_proto_skip (TYPE_8__*,int) ; 
 int /*<<< orphan*/  network_mysqld_proto_skip_network_header (TYPE_8__*) ; 
 int /*<<< orphan*/  parse_resultset_fields (TYPE_7__*) ; 
 int /*<<< orphan*/  proxy_resultset_free (TYPE_7__*) ; 
 TYPE_7__* proxy_resultset_new () ; 

void merge_rows(network_mysqld_con* con, injection* inj) {
	if (!inj->resultset_is_needed || !con->server->recv_queue->chunks || inj->qstat.binary_encoded) return;

	proxy_resultset_t* res = proxy_resultset_new();

	res->result_queue = con->server->recv_queue->chunks;
	res->qstat = inj->qstat;
	res->rows  = inj->rows;
	res->bytes = inj->bytes;

	parse_resultset_fields(res);

	GList* res_row = res->rows_chunk_head;
	while (res_row) {
		network_packet packet;
		packet.data = res_row->data;
		packet.offset = 0;

		network_mysqld_proto_skip_network_header(&packet);
		network_mysqld_lenenc_type lenenc_type;
		network_mysqld_proto_peek_lenenc_type(&packet, &lenenc_type);

		switch (lenenc_type) {
			case NETWORK_MYSQLD_LENENC_TYPE_ERR:
			case NETWORK_MYSQLD_LENENC_TYPE_EOF:
				proxy_resultset_free(res);
				return;

			case NETWORK_MYSQLD_LENENC_TYPE_INT:
			case NETWORK_MYSQLD_LENENC_TYPE_NULL:
				break;
		}

		GPtrArray* row = g_ptr_array_new();

		guint len = res->fields->len;
		guint i;
		for (i = 0; i < len; i++) {
			guint64 field_len;

			network_mysqld_proto_peek_lenenc_type(&packet, &lenenc_type);

			switch (lenenc_type) {
				case NETWORK_MYSQLD_LENENC_TYPE_NULL:
					network_mysqld_proto_skip(&packet, 1);
					break;

				case NETWORK_MYSQLD_LENENC_TYPE_INT:
					network_mysqld_proto_get_lenenc_int(&packet, &field_len);
					g_ptr_array_add(row, g_strndup(packet.data->str + packet.offset, field_len));
					network_mysqld_proto_skip(&packet, field_len);
					break;

				default:
					break;
			}
		}

		g_ptr_array_add(con->merge_res->rows, row);
		if (con->merge_res->rows->len >= con->merge_res->limit) break;
		res_row = res_row->next;
	}

	proxy_resultset_free(res);
}