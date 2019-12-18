#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ offset; TYPE_1__* data; } ;
typedef  TYPE_2__ network_packet ;
struct TYPE_9__ {int /*<<< orphan*/  stmt_text; } ;
typedef  TYPE_3__ network_mysqld_stmt_prepare_packet_t ;
typedef  scalar_t__ guint8 ;
struct TYPE_7__ {scalar_t__ len; scalar_t__ str; } ;

/* Variables and functions */
 scalar_t__ COM_STMT_PREPARE ; 
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  g_string_assign_len (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ network_mysqld_proto_get_int8 (TYPE_2__*,scalar_t__*) ; 

int network_mysqld_proto_get_stmt_prepare_packet(network_packet *packet, network_mysqld_stmt_prepare_packet_t *stmt_prepare_packet) {
	guint8 packet_type;

	int err = 0;

	err = err || network_mysqld_proto_get_int8(packet, &packet_type);
	if (err) return -1;

	if (COM_STMT_PREPARE != packet_type) {
		g_critical("%s: expected the first byte to be %02x, got %02x",
				G_STRLOC,
				COM_STMT_PREPARE,
				packet_type);
		return -1;
	}

	g_string_assign_len(stmt_prepare_packet->stmt_text, packet->data->str + packet->offset, packet->data->len - packet->offset);

	return err ? -1 : 0;
}