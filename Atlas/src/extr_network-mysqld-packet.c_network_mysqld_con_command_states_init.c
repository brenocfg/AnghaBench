#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ offset; } ;
typedef  TYPE_2__ network_packet ;
struct TYPE_9__ {int /*<<< orphan*/  data; void* data_free; int /*<<< orphan*/  command; } ;
struct TYPE_11__ {int /*<<< orphan*/  com_quit_seen; TYPE_1__ parse; } ;
typedef  TYPE_3__ network_mysqld_con ;
typedef  int /*<<< orphan*/  guint8 ;
typedef  void* GDestroyNotify ;

/* Variables and functions */
#define  COM_INIT_DB 133 
#define  COM_PROCESS_INFO 132 
#define  COM_QUERY 131 
#define  COM_QUIT 130 
#define  COM_STMT_EXECUTE 129 
#define  COM_STMT_PREPARE 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  network_mysqld_com_init_db_result_free ; 
 int /*<<< orphan*/  network_mysqld_com_init_db_result_new () ; 
 int /*<<< orphan*/  network_mysqld_com_init_db_result_track_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_com_query_result_free ; 
 int /*<<< orphan*/  network_mysqld_com_query_result_new () ; 
 int /*<<< orphan*/  network_mysqld_com_stmt_prepare_result_free ; 
 int /*<<< orphan*/  network_mysqld_com_stmt_prepare_result_new () ; 
 scalar_t__ network_mysqld_proto_get_int8 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_proto_skip_network_header (TYPE_2__*) ; 

int network_mysqld_con_command_states_init(network_mysqld_con *con, network_packet *packet) {
	guint8 cmd;
	int err = 0;

	err = err || network_mysqld_proto_skip_network_header(packet);
	err = err || network_mysqld_proto_get_int8(packet, &cmd);

	if (err) return -1;

	con->parse.command = cmd;

	packet->offset = 0; /* reset the offset again for the next functions */

	/* init the parser for the commands */
	switch (con->parse.command) {
	case COM_QUERY:
	case COM_PROCESS_INFO:
	case COM_STMT_EXECUTE:
		con->parse.data = network_mysqld_com_query_result_new();
		con->parse.data_free = (GDestroyNotify)network_mysqld_com_query_result_free;
		break;
	case COM_STMT_PREPARE:
		con->parse.data = network_mysqld_com_stmt_prepare_result_new();
		con->parse.data_free = (GDestroyNotify)network_mysqld_com_stmt_prepare_result_free;
		break;
	case COM_INIT_DB:
		con->parse.data = network_mysqld_com_init_db_result_new();
		con->parse.data_free = (GDestroyNotify)network_mysqld_com_init_db_result_free;

		network_mysqld_com_init_db_result_track_state(packet, con->parse.data);

		break;
	case COM_QUIT:
		/* track COM_QUIT going to the server, to be able to tell if the server
		 * a) simply went away or
		 * b) closed the connection because the client asked it to
		 * If b) we should not print a message at the next EV_READ event from the server fd
		 */
		con->com_quit_seen = TRUE;
	default:
		break;
	}

	return 0;
}