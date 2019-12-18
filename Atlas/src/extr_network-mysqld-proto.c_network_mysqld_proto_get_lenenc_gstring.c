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
typedef  int /*<<< orphan*/  guint64 ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 scalar_t__ network_mysqld_proto_get_gstring_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_proto_get_lenenc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int network_mysqld_proto_get_lenenc_gstring(network_packet *packet, GString *out) {
	guint64 len;
	int err = 0;

	err = err || network_mysqld_proto_get_lenenc_int(packet, &len);
	err = err || network_mysqld_proto_get_gstring_len(packet, len, out);

	return err ? -1 : 0;
}