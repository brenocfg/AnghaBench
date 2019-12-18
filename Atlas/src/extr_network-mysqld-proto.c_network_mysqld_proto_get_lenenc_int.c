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
struct TYPE_5__ {size_t offset; TYPE_1__* data; } ;
typedef  TYPE_2__ network_packet ;
typedef  int guint64 ;
typedef  size_t guint ;
struct TYPE_4__ {size_t len; scalar_t__ str; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,size_t,unsigned char) ; 

int network_mysqld_proto_get_lenenc_int(network_packet *packet, guint64 *v) {
	guint off = packet->offset;
	guint64 ret = 0;
	unsigned char *bytestream = (unsigned char *)packet->data->str;

	if (off >= packet->data->len) return -1;
	
	if (bytestream[off] < 251) { /* */
		ret = bytestream[off];
	} else if (bytestream[off] == 252) { /* 2 byte length*/
		if (off + 2 >= packet->data->len) return -1;
		ret = (bytestream[off + 1] << 0) | 
			(bytestream[off + 2] << 8) ;
		off += 2;
	} else if (bytestream[off] == 253) { /* 3 byte */
		if (off + 3 >= packet->data->len) return -1;
		ret = (bytestream[off + 1]   <<  0) | 
			(bytestream[off + 2] <<  8) |
			(bytestream[off + 3] << 16);

		off += 3;
	} else if (bytestream[off] == 254) { /* 8 byte */
		if (off + 8 >= packet->data->len) return -1;
		ret = (bytestream[off + 5] << 0) |
			(bytestream[off + 6] << 8) |
			(bytestream[off + 7] << 16) |
			(bytestream[off + 8] << 24);
		ret <<= 32;

		ret |= (bytestream[off + 1] <<  0) | 
			(bytestream[off + 2] <<  8) |
			(bytestream[off + 3] << 16) |
			(bytestream[off + 4] << 24);
		

		off += 8;
	} else {
		/* if we hit this place we complete have no idea about the protocol */
		g_critical("%s: bytestream[%d] is %d", 
			G_STRLOC,
			off, bytestream[off]);

		/* either ERR (255) or NULL (251) */

		return -1;
	}
	off += 1;

	packet->offset = off;

	*v = ret;

	return 0;
}