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
struct TYPE_4__ {int /*<<< orphan*/  fields; int /*<<< orphan*/  table_name; int /*<<< orphan*/  db_name; } ;
typedef  TYPE_1__ network_mysqld_table ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_fielddefs_free (int /*<<< orphan*/ ) ; 

void network_mysqld_table_free(network_mysqld_table *tbl) {
	if (!tbl) return;

	g_string_free(tbl->db_name, TRUE);
	g_string_free(tbl->table_name, TRUE);

	network_mysqld_proto_fielddefs_free(tbl->fields);

	g_free(tbl);
}