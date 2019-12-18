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
struct TYPE_4__ {scalar_t__ db_name; } ;
typedef  TYPE_1__ network_mysqld_com_init_db_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_string_free (scalar_t__,int /*<<< orphan*/ ) ; 

void network_mysqld_com_init_db_result_free(network_mysqld_com_init_db_result_t *udata) {
	if (udata->db_name) g_string_free(udata->db_name, TRUE);

	g_free(udata);
}