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
struct pmf_function {int dummy; } ;
struct pmf_args {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int pmf_call_one (struct pmf_function*,struct pmf_args*) ; 
 struct pmf_function* pmf_find_function (struct device_node*,char const*) ; 
 int /*<<< orphan*/  pmf_put_function (struct pmf_function*) ; 

int pmf_call_function(struct device_node *target, const char *name,
		      struct pmf_args *args)
{
	struct pmf_function *func = pmf_find_function(target, name);
	int rc;

	if (func == NULL)
		return -ENODEV;

	rc = pmf_call_one(func, args);
	pmf_put_function(func);
	return rc;
}