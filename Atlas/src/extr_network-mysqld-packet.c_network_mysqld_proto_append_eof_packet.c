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
struct TYPE_3__ {int /*<<< orphan*/  server_status; int /*<<< orphan*/  warnings; } ;
typedef  TYPE_1__ network_mysqld_eof_packet_t ;
typedef  int guint32 ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int CLIENT_PROTOCOL_41 ; 
 int /*<<< orphan*/  MYSQLD_PACKET_EOF ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int network_mysqld_proto_append_eof_packet(GString *packet, network_mysqld_eof_packet_t *eof_packet) {
	guint32 capabilities = CLIENT_PROTOCOL_41;

	network_mysqld_proto_append_int8(packet, MYSQLD_PACKET_EOF); /* no fields */
	if (capabilities & CLIENT_PROTOCOL_41) {
		network_mysqld_proto_append_int16(packet, eof_packet->warnings); /* no warnings */
		network_mysqld_proto_append_int16(packet, eof_packet->server_status); /* autocommit */
	}

	return 0;
}