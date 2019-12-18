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
struct TYPE_5__ {int offset; TYPE_1__* data; } ;
typedef  TYPE_2__ network_packet ;
typedef  int guint64 ;
typedef  int guint32 ;
typedef  int guchar ;
typedef  int gsize ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ str; } ;

/* Variables and functions */

int network_mysqld_proto_peek_int_len(network_packet *packet, guint64 *v, gsize size) {
	gsize i;
	int shift;
	guint32 r_l = 0, r_h = 0;
	guchar *bytes = (guchar *)packet->data->str + packet->offset;

	if (packet->offset > packet->data->len) {
		return -1;
	}
	if (packet->offset + size > packet->data->len) {
		return -1;
	}

	/**
	 * for some reason left-shift > 32 leads to negative numbers 
	 */
	for (i = 0, shift = 0; 
			i < size && i < 4; 
			i++, shift += 8, bytes++) {
		r_l |= ((*bytes) << shift);
	}

	for (shift = 0;
			i < size; 
			i++, shift += 8, bytes++) {
		r_h |= ((*bytes) << shift);
	}

	*v = (((guint64)r_h << 32) | r_l);

	return 0;
}