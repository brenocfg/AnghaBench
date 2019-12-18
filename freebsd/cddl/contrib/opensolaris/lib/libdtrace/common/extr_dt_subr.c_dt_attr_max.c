#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* dtat_class; void* dtat_data; void* dtat_name; } ;
typedef  TYPE_1__ dtrace_attribute_t ;

/* Variables and functions */
 void* MAX (void*,void*) ; 

dtrace_attribute_t
dt_attr_max(dtrace_attribute_t a1, dtrace_attribute_t a2)
{
	dtrace_attribute_t am;

	am.dtat_name = MAX(a1.dtat_name, a2.dtat_name);
	am.dtat_data = MAX(a1.dtat_data, a2.dtat_data);
	am.dtat_class = MAX(a1.dtat_class, a2.dtat_class);

	return (am);
}