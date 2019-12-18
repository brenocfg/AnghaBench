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
typedef  int /*<<< orphan*/  network_mysqld_lenenc_type ;
typedef  size_t guint ;
struct TYPE_4__ {size_t len; scalar_t__ str; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETWORK_MYSQLD_LENENC_TYPE_EOF ; 
 int /*<<< orphan*/  NETWORK_MYSQLD_LENENC_TYPE_ERR ; 
 int /*<<< orphan*/  NETWORK_MYSQLD_LENENC_TYPE_INT ; 
 int /*<<< orphan*/  NETWORK_MYSQLD_LENENC_TYPE_NULL ; 
 int /*<<< orphan*/  g_return_val_if_fail (int,int) ; 

int network_mysqld_proto_peek_lenenc_type(network_packet *packet, network_mysqld_lenenc_type *type) {
	guint off = packet->offset;
	unsigned char *bytestream = (unsigned char *)packet->data->str;

	g_return_val_if_fail(off < packet->data->len, -1);

	if (bytestream[off] < 251) { /* */
		*type = NETWORK_MYSQLD_LENENC_TYPE_INT;
	} else if (bytestream[off] == 251) { /* NULL */
		*type = NETWORK_MYSQLD_LENENC_TYPE_NULL;
	} else if (bytestream[off] == 252) { /* 2 byte length*/
		*type = NETWORK_MYSQLD_LENENC_TYPE_INT;
	} else if (bytestream[off] == 253) { /* 3 byte */
		*type = NETWORK_MYSQLD_LENENC_TYPE_INT;
	} else if (bytestream[off] == 254) { /* 8 byte OR EOF */
		if (off == 4 && 
		    packet->data->len - packet->offset < 8) {
			*type = NETWORK_MYSQLD_LENENC_TYPE_EOF;
		} else {
			*type = NETWORK_MYSQLD_LENENC_TYPE_INT;
		}
	} else {
		*type = NETWORK_MYSQLD_LENENC_TYPE_ERR;
	}

	return 0;
}