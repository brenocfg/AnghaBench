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
struct TYPE_3__ {int /*<<< orphan*/  warnings; int /*<<< orphan*/  num_params; int /*<<< orphan*/  num_columns; int /*<<< orphan*/  stmt_id; } ;
typedef  TYPE_1__ network_mysqld_stmt_prepare_ok_packet_t ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int MYSQLD_PACKET_OK ; 
 scalar_t__ network_mysqld_proto_append_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ network_mysqld_proto_append_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ network_mysqld_proto_append_int8 (int /*<<< orphan*/ *,int) ; 

int network_mysqld_proto_append_stmt_prepare_ok_packet(GString *packet, network_mysqld_stmt_prepare_ok_packet_t *stmt_prepare_ok_packet) {
	int err = 0;

	err = err || network_mysqld_proto_append_int8(packet, MYSQLD_PACKET_OK);
	err = err || network_mysqld_proto_append_int32(packet, stmt_prepare_ok_packet->stmt_id);
	err = err || network_mysqld_proto_append_int16(packet, stmt_prepare_ok_packet->num_columns);
	err = err || network_mysqld_proto_append_int16(packet, stmt_prepare_ok_packet->num_params);
	err = err || network_mysqld_proto_append_int8(packet, 0x00);
	err = err || network_mysqld_proto_append_int16(packet, stmt_prepare_ok_packet->warnings);

	return err ? -1 : 0;
}