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
typedef  int /*<<< orphan*/  network_mysqld_type_date_t ;
typedef  int gboolean ;

/* Variables and functions */
 scalar_t__ network_mysqld_type_date_date_is_valid (int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_type_date_time_is_valid (int /*<<< orphan*/ *) ; 

gboolean network_mysqld_type_date_is_valid(network_mysqld_type_date_t *date) {
	return network_mysqld_type_date_time_is_valid(date) &&
		network_mysqld_type_date_date_is_valid(date);
}