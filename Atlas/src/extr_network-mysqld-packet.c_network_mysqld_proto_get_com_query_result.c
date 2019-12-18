#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int offset; TYPE_1__* data; } ;
typedef  TYPE_2__ network_packet ;
struct TYPE_20__ {int server_status; int /*<<< orphan*/  insert_id; int /*<<< orphan*/  affected_rows; int /*<<< orphan*/  warnings; } ;
typedef  TYPE_3__ network_mysqld_ok_packet_t ;
struct TYPE_21__ {int server_status; int /*<<< orphan*/  warnings; } ;
typedef  TYPE_4__ network_mysqld_eof_packet_t ;
typedef  int /*<<< orphan*/  network_mysqld_con ;
struct TYPE_22__ {int state; int query_status; int server_status; int was_resultset; int bytes; int /*<<< orphan*/  rows; int /*<<< orphan*/  warning_count; int /*<<< orphan*/  binary_encoded; int /*<<< orphan*/  insert_id; int /*<<< orphan*/  affected_rows; } ;
typedef  TYPE_5__ network_mysqld_com_query_result_t ;
typedef  int /*<<< orphan*/  guint8 ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_18__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
#define  MYSQLD_PACKET_EOF 136 
#define  MYSQLD_PACKET_ERR 135 
#define  MYSQLD_PACKET_NULL 134 
#define  MYSQLD_PACKET_OK 133 
#define  PARSE_COM_QUERY_FIELD 132 
#define  PARSE_COM_QUERY_INIT 131 
#define  PARSE_COM_QUERY_LOCAL_INFILE_DATA 130 
#define  PARSE_COM_QUERY_LOCAL_INFILE_RESULT 129 
#define  PARSE_COM_QUERY_RESULT 128 
 int SERVER_MORE_RESULTS_EXISTS ; 
 int SERVER_PS_OUT_PARAMS ; 
 int SERVER_STATUS_CURSOR_EXISTS ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_eof_packet_free (TYPE_4__*) ; 
 TYPE_4__* network_mysqld_eof_packet_new () ; 
 int /*<<< orphan*/  network_mysqld_ok_packet_free (TYPE_3__*) ; 
 TYPE_3__* network_mysqld_ok_packet_new () ; 
 int /*<<< orphan*/  network_mysqld_proto_get_eof_packet (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  network_mysqld_proto_get_int8 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_proto_get_ok_packet (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  network_mysqld_proto_peek_int8 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_charset (int /*<<< orphan*/ *) ; 

int network_mysqld_proto_get_com_query_result(network_packet *packet, network_mysqld_com_query_result_t *query, network_mysqld_con *con, gboolean use_binary_row_data) {
	int is_finished = 0;
	guint8 status;
	int err = 0;
	network_mysqld_eof_packet_t *eof_packet;
	network_mysqld_ok_packet_t *ok_packet;

	/**
	 * if we get a OK in the first packet there will be no result-set
	 */
	switch (query->state) {
	case PARSE_COM_QUERY_INIT:
		err = err || network_mysqld_proto_peek_int8(packet, &status);
		if (err) break;

		switch (status) {
		case MYSQLD_PACKET_ERR: /* e.g. SELECT * FROM dual -> ERROR 1096 (HY000): No tables used */
			query->query_status = MYSQLD_PACKET_ERR;
			is_finished = 1;
			break;
		case MYSQLD_PACKET_OK:  /* e.g. DELETE FROM tbl */

			/**
			 * trace the change of charset
			 */
			update_charset(con);
			query->query_status = MYSQLD_PACKET_OK;

			ok_packet = network_mysqld_ok_packet_new();

			err = err || network_mysqld_proto_get_ok_packet(packet, ok_packet);

			if (!err) {
				if (ok_packet->server_status & SERVER_MORE_RESULTS_EXISTS) {
			
				} else {
					is_finished = 1;
				}

				query->server_status = ok_packet->server_status;
				query->warning_count = ok_packet->warnings;
				query->affected_rows = ok_packet->affected_rows;
				query->insert_id     = ok_packet->insert_id;
				query->was_resultset = 0;
				query->binary_encoded= use_binary_row_data; 
			}

			network_mysqld_ok_packet_free(ok_packet);

			break;
		case MYSQLD_PACKET_NULL:
			/* OH NO, LOAD DATA INFILE :) */
			query->state = PARSE_COM_QUERY_LOCAL_INFILE_DATA;
			is_finished = 1;

			break;
		case MYSQLD_PACKET_EOF:
			g_critical("%s: COM_QUERY packet should not be (EOF), got: 0x%02x",
					G_STRLOC,
					status);

			err = 1;

			break;
		default:
			query->query_status = MYSQLD_PACKET_OK;
			/* looks like a result */
			query->state = PARSE_COM_QUERY_FIELD;
			break;
		}
		break;
	case PARSE_COM_QUERY_FIELD:
		err = err || network_mysqld_proto_peek_int8(packet, &status);
		if (err) break;

		switch (status) {
		case MYSQLD_PACKET_ERR:
		case MYSQLD_PACKET_OK:
		case MYSQLD_PACKET_NULL:
			g_critical("%s: COM_QUERY should not be (OK|NULL|ERR), got: 0x%02x",
					G_STRLOC,
					status);

			err = 1;

			break;
		case MYSQLD_PACKET_EOF:
			/**
			 * in 5.0 we have CURSORs which have no rows, just a field definition
			 *
			 * TODO: find a test-case for it, is it COM_STMT_EXECUTE only?
			 */
			if (packet->data->len == 9) {
				eof_packet = network_mysqld_eof_packet_new();

				err = err || network_mysqld_proto_get_eof_packet(packet, eof_packet);

				if (!err) {
#if MYSQL_VERSION_ID >= 50000
					/* 5.5 may send a SERVER_MORE_RESULTS_EXISTS as part of the first 
					 * EOF together with SERVER_STATUS_CURSOR_EXISTS. In that case,
					 * we aren't finished. (#61998)
					 *
					 * Only if _CURSOR_EXISTS is set alone, we have a field-definition-only
					 * resultset
					 */
					if (eof_packet->server_status & SERVER_STATUS_CURSOR_EXISTS &&
					    !(eof_packet->server_status & SERVER_MORE_RESULTS_EXISTS)) {
						is_finished = 1;
					} else {
						query->state = PARSE_COM_QUERY_RESULT;
					}
#else
					query->state = PARSE_COM_QUERY_RESULT;
#endif
					/* track the server_status of the 1st EOF packet */
					query->server_status = eof_packet->server_status;
				}

				network_mysqld_eof_packet_free(eof_packet);
			} else {
				query->state = PARSE_COM_QUERY_RESULT;
			}
			break;
		default:
			break;
		}
		break;
	case PARSE_COM_QUERY_RESULT:
		err = err || network_mysqld_proto_peek_int8(packet, &status);
		if (err) break;

		switch (status) {
		case MYSQLD_PACKET_EOF:
			if (packet->data->len == 9) {
				eof_packet = network_mysqld_eof_packet_new();

				err = err || network_mysqld_proto_get_eof_packet(packet, eof_packet);

				if (!err) {
					query->was_resultset = 1;

#ifndef SERVER_PS_OUT_PARAMS
#define SERVER_PS_OUT_PARAMS 4096
#endif
					/**
					 * a PS_OUT_PARAMS is set if a COM_STMT_EXECUTE executes a CALL sp(?) where sp is a PROCEDURE with OUT params 
					 *
					 * ...
					 * 05 00 00 12 fe 00 00 0a 10 -- end column-def (auto-commit, more-results, ps-out-params)
					 * ...
					 * 05 00 00 14 fe 00 00 02 00 -- end of rows (auto-commit), see the missing (more-results, ps-out-params)
					 * 07 00 00 15 00 00 00 02 00 00 00 -- OK for the CALL
					 *
					 * for all other resultsets we trust the status-flags of the 2nd EOF packet
					 */
					if (!(query->server_status & SERVER_PS_OUT_PARAMS)) {
						query->server_status = eof_packet->server_status;
					}
					query->warning_count = eof_packet->warnings;

					if (query->server_status & SERVER_MORE_RESULTS_EXISTS) {
						query->state = PARSE_COM_QUERY_INIT;
					} else {
						is_finished = 1;
					}
				}

				network_mysqld_eof_packet_free(eof_packet);
			}

			break;
		case MYSQLD_PACKET_ERR:
			/* like 
			 * 
			 * EXPLAIN SELECT * FROM dual; returns an error
			 * 
			 * EXPLAIN SELECT 1 FROM dual; returns a result-set
			 * */
			is_finished = 1;
			break;
		case MYSQLD_PACKET_OK:
		case MYSQLD_PACKET_NULL:
			if (use_binary_row_data) {
				/* fallthrough to default:
				   0x00 is part of the protocol for binary row packets
				 */
			} else {
				/* the first field might be a NULL for a text row packet */
				break;
			}
		default:
			query->rows++;
			query->bytes += packet->data->len;
			break;
		}
		break;
	case PARSE_COM_QUERY_LOCAL_INFILE_DATA: 
		/* we will receive a empty packet if we are done */
		if (packet->data->len == packet->offset) {
			query->state = PARSE_COM_QUERY_LOCAL_INFILE_RESULT;
			is_finished = 1;
		}
		break;
	case PARSE_COM_QUERY_LOCAL_INFILE_RESULT:
		err = err || network_mysqld_proto_get_int8(packet, &status);
		if (err) break;

		switch (status) {
		case MYSQLD_PACKET_OK:
			is_finished = 1;
			break;
		case MYSQLD_PACKET_NULL:
		case MYSQLD_PACKET_ERR:
		case MYSQLD_PACKET_EOF:
		default:
			g_critical("%s: COM_QUERY,should be (OK), got: 0x%02x",
					G_STRLOC,
					status);

			err = 1;

			break;
		}

		break;
	}

	if (err) return -1;

	return is_finished;
}