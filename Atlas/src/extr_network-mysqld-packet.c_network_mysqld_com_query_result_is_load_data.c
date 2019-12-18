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
typedef  int /*<<< orphan*/  network_mysqld_com_query_result_t ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  network_mysqld_com_query_result_is_local_infile (int /*<<< orphan*/ *) ; 

gboolean network_mysqld_com_query_result_is_load_data(network_mysqld_com_query_result_t *udata) {
	return network_mysqld_com_query_result_is_local_infile(udata);
}