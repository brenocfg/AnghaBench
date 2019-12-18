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
typedef  int /*<<< orphan*/  guint8 ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int network_mysqld_proto_append_int8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int network_mysqld_proto_append_packet_id(GString *_header, guint8 id) {
	return network_mysqld_proto_append_int8(_header, id);
}