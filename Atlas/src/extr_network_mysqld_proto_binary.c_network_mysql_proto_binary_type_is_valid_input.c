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
typedef  int /*<<< orphan*/  gboolean ;
typedef  enum enum_field_types { ____Placeholder_enum_field_types } enum_field_types ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  MYSQL_TYPE_BLOB 140 
#define  MYSQL_TYPE_DATE 139 
#define  MYSQL_TYPE_DATETIME 138 
#define  MYSQL_TYPE_DOUBLE 137 
#define  MYSQL_TYPE_FLOAT 136 
#define  MYSQL_TYPE_LONG 135 
#define  MYSQL_TYPE_LONGLONG 134 
#define  MYSQL_TYPE_NULL 133 
#define  MYSQL_TYPE_SHORT 132 
#define  MYSQL_TYPE_STRING 131 
#define  MYSQL_TYPE_TIME 130 
#define  MYSQL_TYPE_TIMESTAMP 129 
#define  MYSQL_TYPE_TINY 128 
 int /*<<< orphan*/  TRUE ; 

gboolean network_mysql_proto_binary_type_is_valid_input(enum enum_field_types field_type) {
	switch (field_type) {
	case MYSQL_TYPE_TINY:
	case MYSQL_TYPE_SHORT:
	case MYSQL_TYPE_LONG:
	case MYSQL_TYPE_LONGLONG:

	case MYSQL_TYPE_FLOAT:
	case MYSQL_TYPE_DOUBLE:

	case MYSQL_TYPE_BLOB:
	case MYSQL_TYPE_STRING:

	case MYSQL_TYPE_DATE:
	case MYSQL_TYPE_DATETIME:
	case MYSQL_TYPE_TIME:
	case MYSQL_TYPE_TIMESTAMP:

	case MYSQL_TYPE_NULL:
		return TRUE;
	default:
		return FALSE;
	}
}