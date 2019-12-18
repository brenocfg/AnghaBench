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
typedef  size_t guint ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/ ** pdata; } ;
typedef  int /*<<< orphan*/  MYSQL_FIELD ;
typedef  TYPE_1__ GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_ptr_array_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_fielddef_free (int /*<<< orphan*/ *) ; 

void network_mysqld_proto_fielddefs_free(GPtrArray *fields) {
	guint i;

	for (i = 0; i < fields->len; i++) {
		MYSQL_FIELD *field = fields->pdata[i];

		if (field) network_mysqld_proto_fielddef_free(field);
	}

	g_ptr_array_free(fields, TRUE);
}