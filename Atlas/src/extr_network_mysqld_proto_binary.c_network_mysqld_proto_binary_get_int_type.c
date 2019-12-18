#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network_packet ;
struct TYPE_4__ {int type; int /*<<< orphan*/  is_unsigned; } ;
typedef  TYPE_1__ network_mysqld_type_t ;
typedef  int /*<<< orphan*/  guint8 ;
typedef  int /*<<< orphan*/  guint64 ;
typedef  int /*<<< orphan*/  guint32 ;
typedef  int /*<<< orphan*/  guint16 ;

/* Variables and functions */
#define  MYSQL_TYPE_INT24 132 
#define  MYSQL_TYPE_LONG 131 
#define  MYSQL_TYPE_LONGLONG 130 
#define  MYSQL_TYPE_SHORT 129 
#define  MYSQL_TYPE_TINY 128 
 int /*<<< orphan*/  network_mysqld_proto_get_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_proto_get_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_proto_get_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_proto_get_int8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_type_set_int (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int network_mysqld_proto_binary_get_int_type(network_packet *packet, network_mysqld_type_t *type) {
	int err = 0;
	guint8 i8;
	guint16 i16;
	guint32 i32;
	guint64 i64;

	switch (type->type) {
	case MYSQL_TYPE_TINY:
		err = err || network_mysqld_proto_get_int8(packet, &i8);
		err = err || network_mysqld_type_set_int(type, (guint64)i8, type->is_unsigned);
		break;
	case MYSQL_TYPE_SHORT:
		err = err || network_mysqld_proto_get_int16(packet, &i16);
		err = err || network_mysqld_type_set_int(type, (guint64)i16, type->is_unsigned);
		break;
	case MYSQL_TYPE_LONG:
	case MYSQL_TYPE_INT24:
		err = err || network_mysqld_proto_get_int32(packet, &i32);
		err = err || network_mysqld_type_set_int(type, (guint64)i32, type->is_unsigned);
		break;
	case MYSQL_TYPE_LONGLONG:
		err = err || network_mysqld_proto_get_int64(packet, &i64);
		err = err || network_mysqld_type_set_int(type, i64, type->is_unsigned);
		break;
	default:
		err = -1;
		break;
	}

	return err ? -1 : 0;
}