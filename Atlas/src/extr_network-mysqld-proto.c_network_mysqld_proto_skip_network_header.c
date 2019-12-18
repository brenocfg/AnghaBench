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

/* Variables and functions */
 int /*<<< orphan*/  NET_HEADER_SIZE ; 
 int network_mysqld_proto_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int network_mysqld_proto_skip_network_header(network_packet *packet) {
	return network_mysqld_proto_skip(packet, NET_HEADER_SIZE);
}