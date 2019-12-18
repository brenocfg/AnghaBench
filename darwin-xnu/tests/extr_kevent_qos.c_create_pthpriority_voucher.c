#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_voucher_t ;
typedef  TYPE_1__* mach_voucher_attr_recipe_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_recipe_data_t ;
typedef  size_t mach_voucher_attr_raw_recipe_size_t ;
typedef  scalar_t__ mach_voucher_attr_raw_recipe_array_t ;
typedef  int /*<<< orphan*/  mach_msg_priority_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_pthread_priority_value_t ;
typedef  int /*<<< orphan*/  ipc_pthread_priority_value ;
struct TYPE_2__ {int content_size; int /*<<< orphan*/ * content; int /*<<< orphan*/  previous_voucher; int /*<<< orphan*/  command; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_PTHPRIORITY ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_PTHPRIORITY_CREATE ; 
 int /*<<< orphan*/  MACH_VOUCHER_NULL ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  host_create_mach_voucher (int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_host_self () ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static mach_voucher_t
create_pthpriority_voucher(mach_msg_priority_t qos)
{
	char voucher_buf[sizeof(mach_voucher_attr_recipe_data_t) + sizeof(ipc_pthread_priority_value_t)];

	mach_voucher_t voucher = MACH_PORT_NULL;
	kern_return_t ret;
	ipc_pthread_priority_value_t ipc_pthread_priority_value =
			(ipc_pthread_priority_value_t)qos;

	mach_voucher_attr_raw_recipe_array_t recipes;
	mach_voucher_attr_raw_recipe_size_t recipe_size = 0;
	mach_voucher_attr_recipe_t recipe =
		(mach_voucher_attr_recipe_t)&voucher_buf[recipe_size];

	recipe->key = MACH_VOUCHER_ATTR_KEY_PTHPRIORITY;
	recipe->command = MACH_VOUCHER_ATTR_PTHPRIORITY_CREATE;
	recipe->previous_voucher = MACH_VOUCHER_NULL;
	memcpy((char *)&recipe->content[0], &ipc_pthread_priority_value, sizeof(ipc_pthread_priority_value));
	recipe->content_size = sizeof(ipc_pthread_priority_value_t);
	recipe_size += sizeof(mach_voucher_attr_recipe_data_t) + recipe->content_size;

	recipes = (mach_voucher_attr_raw_recipe_array_t)&voucher_buf[0];

	ret = host_create_mach_voucher(mach_host_self(),
				recipes,
				recipe_size,
				&voucher);

	T_QUIET; T_ASSERT_MACH_SUCCESS(ret, "client host_create_mach_voucher");
	return voucher;
}