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
typedef  int /*<<< orphan*/  network_packet ;
struct TYPE_3__ {void* warnings; void* server_status; } ;
typedef  TYPE_1__ network_mysqld_eof_packet_t ;
typedef  scalar_t__ guint8 ;
typedef  int guint32 ;
typedef  void* guint16 ;

/* Variables and functions */
 int CLIENT_PROTOCOL_41 ; 
 int /*<<< orphan*/  G_STRLOC ; 
 scalar_t__ MYSQLD_PACKET_EOF ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ network_mysqld_proto_get_int16 (int /*<<< orphan*/ *,void**) ; 
 scalar_t__ network_mysqld_proto_get_int8 (int /*<<< orphan*/ *,scalar_t__*) ; 

int network_mysqld_proto_get_eof_packet(network_packet *packet, network_mysqld_eof_packet_t *eof_packet) {
	guint8 field_count;
	guint16 server_status, warning_count;
	guint32 capabilities = CLIENT_PROTOCOL_41;

	int err = 0;

	err = err || network_mysqld_proto_get_int8(packet, &field_count);
	if (err) return -1;

	if (field_count != MYSQLD_PACKET_EOF) {
		g_critical("%s: expected the first byte to be 0xfe, got %d",
				G_STRLOC,
				field_count);
		return -1;
	}

	if (capabilities & CLIENT_PROTOCOL_41) {
		err = err || network_mysqld_proto_get_int16(packet, &warning_count);
		err = err || network_mysqld_proto_get_int16(packet, &server_status);
		if (!err) {
			eof_packet->server_status = server_status;
			eof_packet->warnings      = warning_count;
		}
	} else {
		eof_packet->server_status = 0;
		eof_packet->warnings      = 0;
	}

	return err ? -1 : 0;
}