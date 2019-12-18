#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stmt_text; } ;
typedef  TYPE_1__ network_mysqld_stmt_prepare_packet_t ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  COM_STMT_PREPARE ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_append_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int network_mysqld_proto_append_stmt_prepare_packet(GString *packet, network_mysqld_stmt_prepare_packet_t *stmt_prepare_packet) {
	network_mysqld_proto_append_int8(packet, COM_STMT_PREPARE);
	g_string_append_len(packet, S(stmt_prepare_packet->stmt_text));

	return 0;
}