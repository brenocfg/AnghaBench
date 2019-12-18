#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* data; } ;
typedef  TYPE_1__ network_mysqld_type_t ;
typedef  scalar_t__ network_mysqld_type_float_t ;

/* Variables and functions */

__attribute__((used)) static int network_mysqld_type_data_float_get_double(network_mysqld_type_t *type, double *dst) {
	network_mysqld_type_float_t *src = type->data;

	if (NULL == type->data) return -1;

	*dst = (double)*src;

	return 0;
}