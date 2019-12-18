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
struct TYPE_10__ {TYPE_2__* comment; TYPE_2__* connect_string; TYPE_2__* se_name; TYPE_2__* col_values; TYPE_2__* screens; TYPE_2__* columns; TYPE_2__* keyinfo; } ;
typedef  TYPE_1__ network_mysqld_frm ;
typedef  size_t guint ;
struct TYPE_11__ {size_t len; struct TYPE_11__** pdata; } ;
typedef  TYPE_2__ GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_ptr_array_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_column_def_free (TYPE_2__*) ; 
 int /*<<< orphan*/  network_mysqld_keyinfo_free (TYPE_2__*) ; 
 int /*<<< orphan*/  network_mysqld_screen_free (TYPE_2__*) ; 

void network_mysqld_frm_free(network_mysqld_frm *frm) {
	guint i;

	if (!frm) return;

	for (i = 0; i < frm->keyinfo->len; i++) {
		network_mysqld_keyinfo_free(frm->keyinfo->pdata[i]);
	}
	g_ptr_array_free(frm->keyinfo, TRUE);

	for (i = 0; i < frm->columns->len; i++) {
		network_mysqld_column_def_free(frm->columns->pdata[i]);
	}
	g_ptr_array_free(frm->columns, TRUE);

	for (i = 0; i < frm->screens->len; i++) {
		network_mysqld_screen_free(frm->screens->pdata[i]);
	}
	g_ptr_array_free(frm->screens, TRUE);

	for (i = 0; i < frm->col_values->len; i++) {
		guint j;
		GPtrArray *values = frm->col_values->pdata[i];

		for (j = 0; j < values->len; j++) {
			g_string_free(values->pdata[i], TRUE);
		}
		g_ptr_array_free(values, TRUE);
	}
	g_ptr_array_free(frm->col_values, TRUE);

	g_string_free(frm->se_name, TRUE);
	g_string_free(frm->connect_string, TRUE);
	g_string_free(frm->comment, TRUE);

	g_free(frm);
}