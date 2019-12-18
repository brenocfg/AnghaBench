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
typedef  int /*<<< orphan*/  guint32 ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int network_mysqld_proto_append_int24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int network_mysqld_proto_append_packet_len(GString *_header, guint32 length) {
	return network_mysqld_proto_append_int24(_header, length);
}