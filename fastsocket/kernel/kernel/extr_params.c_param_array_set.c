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
struct kparam_array {scalar_t__ num; int /*<<< orphan*/  set; int /*<<< orphan*/  elemsize; int /*<<< orphan*/  elem; int /*<<< orphan*/  max; } ;
struct kernel_param {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; struct kparam_array* arr; } ;

/* Variables and functions */
 int param_array (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

int param_array_set(const char *val, struct kernel_param *kp)
{
	const struct kparam_array *arr = kp->arr;
	unsigned int temp_num;

	return param_array(kp->name, val, 1, arr->max, arr->elem,
			   arr->elemsize, arr->set, kp->flags,
			   arr->num ?: &temp_num);
}