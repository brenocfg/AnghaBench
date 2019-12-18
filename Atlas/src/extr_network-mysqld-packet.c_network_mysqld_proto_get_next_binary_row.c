#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ offset; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ network_packet ;
typedef  int /*<<< orphan*/  network_mysqld_resultset_row_t ;
typedef  int /*<<< orphan*/  network_mysqld_proto_fielddefs_t ;
typedef  scalar_t__ network_mysqld_lenenc_type ;
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 scalar_t__ NETWORK_MYSQLD_LENENC_TYPE_EOF ; 
 scalar_t__ network_mysqld_proto_get_binary_row (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_proto_peek_lenenc_type (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ network_mysqld_proto_skip_network_header (TYPE_1__*) ; 

GList *network_mysqld_proto_get_next_binary_row(GList *chunk, network_mysqld_proto_fielddefs_t *fields, network_mysqld_resultset_row_t *row) {
	network_packet packet;
	int err = 0;
	network_mysqld_lenenc_type lenenc_type;
    
	packet.data = chunk->data;
	packet.offset = 0;

	err = err || network_mysqld_proto_skip_network_header(&packet);

	err = err || network_mysqld_proto_peek_lenenc_type(&packet, &lenenc_type);
	if (0 != err) return NULL;

	if (NETWORK_MYSQLD_LENENC_TYPE_EOF == lenenc_type) {
		/* this is a EOF packet, we are done */
		return NULL;
	}

	err = err || network_mysqld_proto_get_binary_row(&packet, fields, row);

	return err ? NULL : chunk->next;
}