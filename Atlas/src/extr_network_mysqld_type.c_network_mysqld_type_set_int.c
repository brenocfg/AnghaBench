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
struct TYPE_4__ {int (* set_int ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ network_mysqld_type_t ;
typedef  int /*<<< orphan*/  guint64 ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int network_mysqld_type_set_int(network_mysqld_type_t *type, guint64 i, gboolean is_unsigned) {
	if (NULL == type->set_int) return -1;

	return type->set_int(type, i, is_unsigned);
}