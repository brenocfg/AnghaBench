#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ offset; TYPE_1__* data; } ;
typedef  TYPE_2__ network_packet ;
typedef  scalar_t__ gsize ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ str; } ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  g_string_append_len (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  g_string_truncate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int network_mysqld_proto_get_gstring_len(network_packet *packet, gsize len, GString *out) {
	int err = 0;

	if (!out) return -1;

	g_string_truncate(out, 0);

	if (!len) return 0; /* nothing to copy */

	err = err || (packet->offset >= packet->data->len); /* the offset is already too large */
	err = err || (packet->offset + len > packet->data->len); /* offset would get too large */

	if (!err) {
		g_string_append_len(out, packet->data->str + packet->offset, len);
		packet->offset += len;
	}

	return err ? -1 : 0;
}