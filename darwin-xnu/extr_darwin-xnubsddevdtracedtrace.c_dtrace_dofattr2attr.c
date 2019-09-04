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
 int /*<<< orphan*/  DOF_ATTR_CLASS (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DOF_ATTR_DATA (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DOF_ATTR_NAME (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
dtrace_dofattr2attr(dtrace_attribute_t *attr, const dof_attr_t dofattr)
{
	attr->dtat_name = DOF_ATTR_NAME(dofattr);
	attr->dtat_data = DOF_ATTR_DATA(dofattr);
	attr->dtat_class = DOF_ATTR_CLASS(dofattr);
}