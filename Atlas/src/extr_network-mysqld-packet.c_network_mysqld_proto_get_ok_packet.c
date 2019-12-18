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
struct TYPE_3__ {void* warnings; void* server_status; void* insert_id; void* affected_rows; } ;
typedef  TYPE_1__ network_mysqld_ok_packet_t ;
typedef  scalar_t__ guint8 ;
typedef  void* guint64 ;
typedef  int guint32 ;
typedef  void* guint16 ;

/* Variables and functions */
 int CLIENT_PROTOCOL_41 ; 
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ network_mysqld_proto_get_int16 (int /*<<< orphan*/ *,void**) ; 
 scalar_t__ network_mysqld_proto_get_int8 (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ network_mysqld_proto_get_lenenc_int (int /*<<< orphan*/ *,void**) ; 

int network_mysqld_proto_get_ok_packet(network_packet *packet, network_mysqld_ok_packet_t *ok_packet) {
	guint8 field_count;
	guint64 affected, insert_id;
	guint16 server_status, warning_count = 0;
	guint32 capabilities = CLIENT_PROTOCOL_41;

	int err = 0;

	err = err || network_mysqld_proto_get_int8(packet, &field_count);
	if (err) return -1;

	if (field_count != 0) {
		g_critical("%s: expected the first byte to be 0, got %d",
				G_STRLOC,
				field_count);
		return -1;
	}

	err = err || network_mysqld_proto_get_lenenc_int(packet, &affected);
	err = err || network_mysqld_proto_get_lenenc_int(packet, &insert_id);
	err = err || network_mysqld_proto_get_int16(packet, &server_status);
	if (capabilities & CLIENT_PROTOCOL_41) {
		err = err || network_mysqld_proto_get_int16(packet, &warning_count);
	}

	if (!err) {
		ok_packet->affected_rows = affected;
		ok_packet->insert_id     = insert_id;
		ok_packet->server_status = server_status;
		ok_packet->warnings      = warning_count;
	}

	return err ? -1 : 0;
}