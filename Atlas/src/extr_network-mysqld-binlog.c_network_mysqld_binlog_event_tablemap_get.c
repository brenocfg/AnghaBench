#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ offset; TYPE_7__* data; } ;
typedef  TYPE_3__ network_packet ;
struct TYPE_17__ {int /*<<< orphan*/  fields; int /*<<< orphan*/  table_id; int /*<<< orphan*/  table_name; int /*<<< orphan*/  db_name; } ;
typedef  TYPE_4__ network_mysqld_table ;
struct TYPE_14__ {scalar_t__ metadata_len; int columns_len; int* null_bits; scalar_t__* metadata; scalar_t__* columns; int /*<<< orphan*/  table_id; int /*<<< orphan*/  table_name; int /*<<< orphan*/  db_name; } ;
struct TYPE_15__ {TYPE_1__ table_map_event; } ;
struct TYPE_18__ {TYPE_2__ event; } ;
typedef  TYPE_5__ network_mysqld_binlog_event ;
typedef  int guint8 ;
typedef  int guint16 ;
typedef  int guint ;
typedef  int guchar ;
typedef  enum enum_field_types { ____Placeholder_enum_field_types } enum_field_types ;
struct TYPE_20__ {scalar_t__ len; scalar_t__* str; } ;
struct TYPE_19__ {int max_length; int type; int decimals; int /*<<< orphan*/  flags; } ;
typedef  TYPE_6__ MYSQL_FIELD ;
typedef  TYPE_7__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
#define  MYSQL_TYPE_BIT 148 
#define  MYSQL_TYPE_BLOB 147 
#define  MYSQL_TYPE_DATE 146 
#define  MYSQL_TYPE_DATETIME 145 
#define  MYSQL_TYPE_DECIMAL 144 
#define  MYSQL_TYPE_DOUBLE 143 
#define  MYSQL_TYPE_ENUM 142 
#define  MYSQL_TYPE_FLOAT 141 
#define  MYSQL_TYPE_GEOMETRY 140 
#define  MYSQL_TYPE_INT24 139 
#define  MYSQL_TYPE_LONG 138 
#define  MYSQL_TYPE_LONGLONG 137 
 int MYSQL_TYPE_LONG_BLOB ; 
 int MYSQL_TYPE_MEDIUM_BLOB ; 
#define  MYSQL_TYPE_NEWDECIMAL 136 
#define  MYSQL_TYPE_SHORT 135 
#define  MYSQL_TYPE_STRING 134 
#define  MYSQL_TYPE_TIME 133 
#define  MYSQL_TYPE_TIMESTAMP 132 
#define  MYSQL_TYPE_TINY 131 
 int const MYSQL_TYPE_TINY_BLOB ; 
#define  MYSQL_TYPE_VARCHAR 130 
#define  MYSQL_TYPE_VAR_STRING 129 
#define  MYSQL_TYPE_YEAR 128 
 int /*<<< orphan*/  NOT_NULL_FLAG ; 
 int /*<<< orphan*/  g_assert_not_reached () ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_debug_hexdump (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  g_error (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_ptr_array_add (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  g_string_assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* network_mysqld_proto_fielddef_new () ; 
 int /*<<< orphan*/  network_mysqld_proto_get_int16 (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  network_mysqld_proto_get_int8 (TYPE_3__*,int*) ; 

int network_mysqld_binlog_event_tablemap_get(
		network_mysqld_binlog_event *event,
		network_mysqld_table *tbl) {

	network_packet metadata_packet;
	GString row;
	guint i;
	int err = 0;

	g_string_assign(tbl->db_name, event->event.table_map_event.db_name);
	g_string_assign(tbl->table_name, event->event.table_map_event.table_name);

	tbl->table_id = event->event.table_map_event.table_id;

	row.str = event->event.table_map_event.metadata;
	row.len = event->event.table_map_event.metadata_len;

	metadata_packet.data = &row;
	metadata_packet.offset = 0;

	/* the metadata is field specific */
	for (i = 0; i < event->event.table_map_event.columns_len; i++) {
		MYSQL_FIELD *field = network_mysqld_proto_fielddef_new();
		enum enum_field_types col_type;
		guint8 byte0, byte1;
		guint16 varchar_length;

		guint byteoffset = i / 8;
		guint bitoffset = i % 8;

		field->flags |= (event->event.table_map_event.null_bits[byteoffset] >> bitoffset) & 0x1 ? 0 : NOT_NULL_FLAG;

		col_type = (enum enum_field_types)event->event.table_map_event.columns[i];

		/* the meta-data depends on the type,
		 *
		 * string has 2 byte field-length
		 * floats have precision
		 * ints have display length
		 * */
		switch ((guchar)col_type) {
		case MYSQL_TYPE_STRING: /* 254 (CHAR) */
			/**
			 * due to #37426 the encoding is a bit tricky in 5.1.26+
			 * as we need at least 10 bits to encode the max-field-length
			 *
			 * < 5.1.26
			 *
			 *   byte0      byte1
			 *   xxxx xxxx  .... ....  real-type
			 *   .... ....  xxxx xxxx  field-length
			 *   7       0  7       0
			 *
			 * >= 5.1.26
			 *   byte0      byte1
			 *   xx11 xxxx  .... ....  real-type
			 *   ..xx ....  xxxx xxxx  field-length
			 *   7       0  7       0
			 * 
			 */

			/* byte 0: real_type + upper bits of field-length (see #37426)
			 * byte 1: field-length
			 */
			err = err || network_mysqld_proto_get_int8(&metadata_packet, 
					&byte0);
			err = err || network_mysqld_proto_get_int8(&metadata_packet, 
					&byte1);
			if (!err) {
				if ((byte0 & 0x30) != 0x30) {
					/* a long CHAR() field */
					field->max_length |= (((byte0 & 0x30) ^ 0x30) << 4);
					field->type = byte0 | 0x30; /* see #37426 */
				} else {
					field->max_length = byte1;
					field->type       = byte0;
				}
			}

			break;
		case MYSQL_TYPE_VARCHAR: /* 15 (VARCHAR) */
		case MYSQL_TYPE_VAR_STRING:
			/* 2 byte length (int2store)
			 */
			err = err || network_mysqld_proto_get_int16(&metadata_packet, &varchar_length);

			if (!err) {
				field->type = col_type;
				field->max_length = varchar_length;
			}
			break;
		case MYSQL_TYPE_GEOMETRY: /* 255 */
		case MYSQL_TYPE_BLOB: /* 252 */
			/* the packlength (1 .. 4) */
			err = err || network_mysqld_proto_get_int8(&metadata_packet, &byte0);

			if (!err) {
				field->type = (guchar)col_type;
				field->max_length = byte0;

				/* fix the field-type */
				if (field->type == MYSQL_TYPE_BLOB) {
					switch (field->max_length) {
					case 1:
						field->type = MYSQL_TYPE_TINY_BLOB;
						break;
					case 2:
						field->type = MYSQL_TYPE_BLOB;
						break;
					case 3:
						field->type = MYSQL_TYPE_MEDIUM_BLOB;
						break;
					case 4:
						field->type = MYSQL_TYPE_LONG_BLOB;
						break;
					default:
						err = 1;
						break;
					}
				} else if (field->type == MYSQL_TYPE_GEOMETRY) {
					if (field->max_length != 4) {
						err = 1;
					}
				} else {
					g_assert_not_reached();
				}
			}

			break;
		case MYSQL_TYPE_NEWDECIMAL:
			field->type = col_type;
			/**
			 * byte 0: precisions
			 * byte 1: decimals
			 */
			err = err || network_mysqld_proto_get_int8(&metadata_packet, &byte0);
			err = err || network_mysqld_proto_get_int8(&metadata_packet, &byte1);

			if (!err) {
				field->max_length = byte0;
				field->decimals   = byte1;
			}
			break;
		case MYSQL_TYPE_DOUBLE:
		case MYSQL_TYPE_FLOAT:
			/* pack-length */
			err = err || network_mysqld_proto_get_int8(&metadata_packet, &byte0);

			if (!err) {
				field->type = col_type;
				field->max_length = byte0;
			}
			break;
		case MYSQL_TYPE_ENUM:
			/* real-type (ENUM|SET)
			 * pack-length
			 */
			err = err || network_mysqld_proto_get_int8(&metadata_packet, &byte0);
			err = err || network_mysqld_proto_get_int8(&metadata_packet, &byte1);

			if (!err) {
				field->type = byte0;
				field->max_length = byte1;
			}
			break;
		case MYSQL_TYPE_BIT:
			/*
			 * [0] - bitlength % 8
			 * [1] - bitlength / 8
			 */
			field->type = col_type;

			err = err || network_mysqld_proto_get_int8(&metadata_packet, &byte0);
			err = err || network_mysqld_proto_get_int8(&metadata_packet, &byte1);

			if (!err) {
				field->max_length = byte1 + (byte0 == 0 ? 0 : 1);
			}

			break;

		/* no metadata */
		case MYSQL_TYPE_DECIMAL:
		case MYSQL_TYPE_DATE: 
		case MYSQL_TYPE_DATETIME:
		case MYSQL_TYPE_TIME:
		case MYSQL_TYPE_TIMESTAMP:
		case MYSQL_TYPE_YEAR:

		case MYSQL_TYPE_TINY:
		case MYSQL_TYPE_SHORT:
		case MYSQL_TYPE_INT24:
		case MYSQL_TYPE_LONG:
		case MYSQL_TYPE_LONGLONG:
			field->type = col_type;
			break;
		default:
			g_error("%s: field-type %d isn't handled",
					G_STRLOC,
					col_type
					);
			break;
		}

		g_ptr_array_add(tbl->fields, field);
	}

	if (metadata_packet.offset != metadata_packet.data->len) {
		g_debug_hexdump(G_STRLOC, event->event.table_map_event.columns, event->event.table_map_event.columns_len);
		g_debug_hexdump(G_STRLOC, event->event.table_map_event.metadata, event->event.table_map_event.metadata_len);
	}
	if (metadata_packet.offset != metadata_packet.data->len) {
		g_critical("%s: ",
				G_STRLOC);
		err = 1;
	}

	return err ? -1 : 0;
}