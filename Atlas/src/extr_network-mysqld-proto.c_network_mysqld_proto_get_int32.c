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
typedef  int guint64 ;
typedef  int guint32 ;

/* Variables and functions */
 scalar_t__ network_mysqld_proto_get_int_len (int /*<<< orphan*/ *,int*,int) ; 

int network_mysqld_proto_get_int32(network_packet *packet, guint32 *v) {
	guint64 v64;

	if (network_mysqld_proto_get_int_len(packet, &v64, 4)) return -1;

	*v = v64 & 0xffffffff;

	return 0;
}