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
struct TYPE_3__ {int /*<<< orphan*/  binlog_file; int /*<<< orphan*/  server_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  binlog_pos; } ;
typedef  TYPE_1__ network_mysqld_binlog_dump ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  COM_BINLOG_DUMP ; 
 int /*<<< orphan*/  g_string_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_append_int8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int network_mysqld_proto_append_binlog_dump(GString *packet, network_mysqld_binlog_dump *dump) {
	network_mysqld_proto_append_int8(packet, COM_BINLOG_DUMP);
	network_mysqld_proto_append_int32(packet, dump->binlog_pos);
	network_mysqld_proto_append_int16(packet, dump->flags); /* flags */
	network_mysqld_proto_append_int32(packet, dump->server_id);
	g_string_append(packet, dump->binlog_file); /* filename */
	network_mysqld_proto_append_int8(packet, 0); /* term-nul */

	return 0;
}