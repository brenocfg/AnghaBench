#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network_mysqld_type_t ;
struct TYPE_5__ {scalar_t__ len; } ;
typedef  TYPE_1__ network_mysqld_resultset_row_t ;
typedef  scalar_t__ guint ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_ptr_array_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_ptr_array_index (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  network_mysqld_type_free (int /*<<< orphan*/ *) ; 

void network_mysqld_resultset_row_free(network_mysqld_resultset_row_t *row) {
	guint i;

	if (NULL == row) return;

	for (i = 0; i < row->len; i++) {
		network_mysqld_type_t *field = g_ptr_array_index(row, i);

		network_mysqld_type_free(field);
	}

	g_ptr_array_free(row, TRUE);
}