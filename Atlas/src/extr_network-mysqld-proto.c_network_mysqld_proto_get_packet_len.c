#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char guint32 ;
struct TYPE_3__ {scalar_t__ str; } ;
typedef  TYPE_1__ GString ;

/* Variables and functions */

guint32 network_mysqld_proto_get_packet_len(GString *_header) {
	unsigned char *header = (unsigned char *)_header->str;

	return header[0] | header[1] << 8 | header[2] << 16;
}