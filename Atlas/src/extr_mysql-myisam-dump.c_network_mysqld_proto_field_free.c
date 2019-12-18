#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* s; } ;
struct TYPE_8__ {TYPE_2__* fielddef; TYPE_1__ data; } ;
typedef  TYPE_3__ network_mysqld_proto_field ;
typedef  int /*<<< orphan*/  guchar ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
#define  MYSQL_TYPE_BLOB 141 
#define  MYSQL_TYPE_DATE 140 
#define  MYSQL_TYPE_DATETIME 139 
#define  MYSQL_TYPE_DECIMAL 138 
#define  MYSQL_TYPE_ENUM 137 
#define  MYSQL_TYPE_INT24 136 
#define  MYSQL_TYPE_LONG 135 
#define  MYSQL_TYPE_NEWDECIMAL 134 
#define  MYSQL_TYPE_SHORT 133 
#define  MYSQL_TYPE_STRING 132 
#define  MYSQL_TYPE_TIMESTAMP 131 
#define  MYSQL_TYPE_TINY 130 
#define  MYSQL_TYPE_VARCHAR 129 
#define  MYSQL_TYPE_VAR_STRING 128 
 int /*<<< orphan*/  g_free (TYPE_3__*) ; 
 int /*<<< orphan*/  g_message (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void network_mysqld_proto_field_free(network_mysqld_proto_field *field) {
	if (!field) return;

	switch ((guchar)field->fielddef->type) {
	case MYSQL_TYPE_TIMESTAMP:
	case MYSQL_TYPE_DATE:
	case MYSQL_TYPE_DATETIME:

	case MYSQL_TYPE_TINY:
	case MYSQL_TYPE_SHORT:
	case MYSQL_TYPE_INT24:
	case MYSQL_TYPE_LONG:

	case MYSQL_TYPE_DECIMAL:
	case MYSQL_TYPE_NEWDECIMAL:

	case MYSQL_TYPE_ENUM:
		break;
	case MYSQL_TYPE_BLOB:
	case MYSQL_TYPE_VARCHAR:
	case MYSQL_TYPE_VAR_STRING:
	case MYSQL_TYPE_STRING:
		if (field->data.s) g_free(field->data.s);
		break;
	default:
		g_message("%s: unknown field_type to free: %d",
				G_STRLOC,
				field->fielddef->type);
		break;
	}

	g_free(field);
}