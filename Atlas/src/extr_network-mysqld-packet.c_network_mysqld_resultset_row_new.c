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
typedef  int /*<<< orphan*/  network_mysqld_resultset_row_t ;

/* Variables and functions */
 int /*<<< orphan*/ * g_ptr_array_new () ; 

network_mysqld_resultset_row_t *network_mysqld_resultset_row_new() {
	return g_ptr_array_new();
}