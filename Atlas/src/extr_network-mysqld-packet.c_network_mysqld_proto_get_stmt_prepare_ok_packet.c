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
struct TYPE_3__ {void* warnings; void* num_params; void* num_columns; int /*<<< orphan*/  stmt_id; } ;
typedef  TYPE_1__ network_mysqld_stmt_prepare_ok_packet_t ;
typedef  int guint8 ;
typedef  int /*<<< orphan*/  guint32 ;
typedef  void* guint16 ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ network_mysqld_proto_get_int16 (int /*<<< orphan*/ *,void**) ; 
 scalar_t__ network_mysqld_proto_get_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_proto_get_int8 (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ network_mysqld_proto_skip (int /*<<< orphan*/ *,int) ; 

int network_mysqld_proto_get_stmt_prepare_ok_packet(network_packet *packet, network_mysqld_stmt_prepare_ok_packet_t *stmt_prepare_ok_packet) {
	guint8 packet_type;
	guint16 num_columns;
	guint16 num_params;
	guint16 warnings;
	guint32 stmt_id;

	int err = 0;

	err = err || network_mysqld_proto_get_int8(packet, &packet_type);
	if (err) return -1;

	if (0x00 != packet_type) {
		g_critical("%s: expected the first byte to be %02x, got %02x",
				G_STRLOC,
				0x00,
				packet_type);
		return -1;
	}
	err = err || network_mysqld_proto_get_int32(packet, &stmt_id);
	err = err || network_mysqld_proto_get_int16(packet, &num_columns);
	err = err || network_mysqld_proto_get_int16(packet, &num_params);
	err = err || network_mysqld_proto_skip(packet, 1); /* the filler */
	err = err || network_mysqld_proto_get_int16(packet, &warnings);

	if (!err) {
		stmt_prepare_ok_packet->stmt_id = stmt_id;
		stmt_prepare_ok_packet->num_columns = num_columns;
		stmt_prepare_ok_packet->num_params = num_params;
		stmt_prepare_ok_packet->warnings = warnings;
	}

	return err ? -1 : 0;
}