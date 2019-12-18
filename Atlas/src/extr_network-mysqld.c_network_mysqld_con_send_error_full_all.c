#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  send_queue; } ;
typedef  TYPE_1__ network_socket ;
struct TYPE_11__ {int /*<<< orphan*/  sqlstate; int /*<<< orphan*/  errmsg; int /*<<< orphan*/  errcode; } ;
typedef  TYPE_2__ network_mysqld_err_packet_t ;
typedef  int /*<<< orphan*/  guint ;
typedef  int /*<<< orphan*/  gsize ;
typedef  char gchar ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_string_assign_len (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_sized_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_err_packet_free (TYPE_2__*) ; 
 TYPE_2__* network_mysqld_err_packet_new () ; 
 TYPE_2__* network_mysqld_err_packet_new_pre41 () ; 
 int /*<<< orphan*/  network_mysqld_proto_append_err_packet (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  network_mysqld_queue_append (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_queue_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int network_mysqld_con_send_error_full_all(network_socket *con,
		const char *errmsg, gsize errmsg_len,
		guint errorcode,
		const gchar *sqlstate,
		gboolean is_41_protocol) {
	GString *packet;
	network_mysqld_err_packet_t *err_packet;

	packet = g_string_sized_new(10 + errmsg_len);
	
	err_packet = is_41_protocol ? network_mysqld_err_packet_new() : network_mysqld_err_packet_new_pre41();
	err_packet->errcode = errorcode;
	if (errmsg) g_string_assign_len(err_packet->errmsg, errmsg, errmsg_len);
	if (sqlstate) g_string_assign_len(err_packet->sqlstate, sqlstate, strlen(sqlstate));

	network_mysqld_proto_append_err_packet(packet, err_packet);

	network_mysqld_queue_append(con, con->send_queue, S(packet));
	network_mysqld_queue_reset(con);

	network_mysqld_err_packet_free(err_packet);
	g_string_free(packet, TRUE);

	return 0;
}