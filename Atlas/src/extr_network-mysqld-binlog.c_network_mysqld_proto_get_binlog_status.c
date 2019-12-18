#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  network_packet ;
typedef  scalar_t__ guint8 ;

/* Variables and functions */
 int /*<<< orphan*/  g_return_val_if_fail (int,int) ; 
 scalar_t__ network_mysqld_proto_get_int8 (int /*<<< orphan*/ *,scalar_t__*) ; 

int network_mysqld_proto_get_binlog_status(network_packet *packet) {
	guint8 ok;

	/* on the network we have a length and packet-number of 4 bytes */
	if (0 != network_mysqld_proto_get_int8(packet, &ok)) {
		return -1;
	}
	g_return_val_if_fail(ok == 0, -1);

	return 0;
}