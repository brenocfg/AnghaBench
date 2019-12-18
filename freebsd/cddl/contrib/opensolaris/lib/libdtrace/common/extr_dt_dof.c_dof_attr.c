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
struct TYPE_3__ {int /*<<< orphan*/  dtat_class; int /*<<< orphan*/  dtat_data; int /*<<< orphan*/  dtat_name; } ;
typedef  TYPE_1__ dtrace_attribute_t ;
typedef  int /*<<< orphan*/  dof_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOF_ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dof_attr_t
dof_attr(const dtrace_attribute_t *ap)
{
	return (DOF_ATTR(ap->dtat_name, ap->dtat_data, ap->dtat_class));
}