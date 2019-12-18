#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ offset; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ network_packet ;
typedef  int /*<<< orphan*/  network_mysqld_proto_fielddef_t ;
typedef  int network_mysqld_lenenc_type ;
typedef  scalar_t__ guint64 ;
typedef  int /*<<< orphan*/  guint32 ;
typedef  scalar_t__ guint ;
struct TYPE_11__ {int /*<<< orphan*/  data; struct TYPE_11__* next; } ;
typedef  int /*<<< orphan*/  GPtrArray ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_PROTOCOL_41 ; 
 int NETWORK_MYSQLD_LENENC_TYPE_EOF ; 
#define  NETWORK_MYSQLD_LENENC_TYPE_INT 128 
 int /*<<< orphan*/  g_assert (TYPE_2__*) ; 
 int /*<<< orphan*/  g_ptr_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * network_mysqld_proto_fielddef_new () ; 
 scalar_t__ network_mysqld_proto_get_fielddef (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ network_mysqld_proto_get_lenenc_int (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ network_mysqld_proto_peek_lenenc_type (TYPE_1__*,int*) ; 
 scalar_t__ network_mysqld_proto_skip_network_header (TYPE_1__*) ; 

GList *network_mysqld_proto_get_fielddefs(GList *chunk, GPtrArray *fields) {
	network_packet packet;
	guint64 field_count;
	guint i;
	int err = 0;
	guint32 capabilities = CLIENT_PROTOCOL_41;
	network_mysqld_lenenc_type lenenc_type;
    
	packet.data = chunk->data;
	packet.offset = 0;

	err = err || network_mysqld_proto_skip_network_header(&packet);
	
	err = err || network_mysqld_proto_peek_lenenc_type(&packet, &lenenc_type);

	if (err) return NULL; /* packet too short */

	/* make sure that we have a valid length-encoded integer here */
	switch (lenenc_type) {
	case NETWORK_MYSQLD_LENENC_TYPE_INT:
		break;
	default:
		/* we shouldn't be here, we expected to get a valid length-encoded field count */
		return NULL;
	}
	
	err = err || network_mysqld_proto_get_lenenc_int(&packet, &field_count);
	
	if (err) return NULL; /* packet to short */

	if (field_count == 0) {
		/* shouldn't happen, the upper layer should have checked that this is a OK packet */
		return NULL;
	}
    
	/* the next chunk, the field-def */
	for (i = 0; i < field_count; i++) {
		network_mysqld_proto_fielddef_t *field;
        
		chunk = chunk->next;
		g_assert(chunk);

		packet.data = chunk->data;
		packet.offset = 0;

		field = network_mysqld_proto_fielddef_new();

		err = err || network_mysqld_proto_skip_network_header(&packet);
		err = err || network_mysqld_proto_get_fielddef(&packet, field, capabilities);

		g_ptr_array_add(fields, field); /* even if we had an error, append it so that we can free it later */

		if (err) return NULL;
	}
    
	/* this should be EOF chunk */
	chunk = chunk->next;

	if (!chunk) return NULL;

	packet.data = chunk->data;
	packet.offset = 0;
	
	err = err || network_mysqld_proto_skip_network_header(&packet);

	err = err || network_mysqld_proto_peek_lenenc_type(&packet, &lenenc_type);
	err = err || (lenenc_type != NETWORK_MYSQLD_LENENC_TYPE_EOF);

	if (err) return NULL;
    
	return chunk;
}