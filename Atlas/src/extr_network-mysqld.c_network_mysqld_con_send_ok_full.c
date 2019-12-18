#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  send_queue; } ;
typedef  TYPE_1__ network_socket ;
struct TYPE_10__ {void* warnings; void* server_status; void* insert_id; void* affected_rows; } ;
typedef  TYPE_2__ network_mysqld_ok_packet_t ;
typedef  void* guint64 ;
typedef  void* guint16 ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_ok_packet_free (TYPE_2__*) ; 
 TYPE_2__* network_mysqld_ok_packet_new () ; 
 int /*<<< orphan*/  network_mysqld_proto_append_ok_packet (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  network_mysqld_queue_append (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_queue_reset (TYPE_1__*) ; 

int network_mysqld_con_send_ok_full(network_socket *con, guint64 affected_rows, guint64 insert_id, guint16 server_status, guint16 warnings ) {
	GString *packet = g_string_new(NULL);
	network_mysqld_ok_packet_t *ok_packet;

	ok_packet = network_mysqld_ok_packet_new();
	ok_packet->affected_rows = affected_rows;
	ok_packet->insert_id     = insert_id;
	ok_packet->server_status = server_status;
	ok_packet->warnings      = warnings;

	network_mysqld_proto_append_ok_packet(packet, ok_packet);
	
	network_mysqld_queue_append(con, con->send_queue, S(packet));
	network_mysqld_queue_reset(con);

	g_string_free(packet, TRUE);
	network_mysqld_ok_packet_free(ok_packet);

	return 0;
}