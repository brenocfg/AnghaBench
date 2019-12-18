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
struct TYPE_4__ {int (* get_date ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ network_mysqld_type_t ;
typedef  int /*<<< orphan*/  network_mysqld_type_date_t ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

int network_mysqld_type_get_date(network_mysqld_type_t *type, network_mysqld_type_date_t *date) {
	if (NULL == type->get_date) return -1;

	return type->get_date(type, date);
}