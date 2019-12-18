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
struct kcdata_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  kcdata_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ,int) ; 

kern_return_t kcdata_memory_destroy(kcdata_descriptor_t data)
{
	if (!data) {
		return KERN_INVALID_ARGUMENT;
	}

	/*
	 * data->kcd_addr_begin points to memory in not tracked by
	 * kcdata lib. So not clearing that here.
	 */
	kfree(data, sizeof(struct kcdata_descriptor));
	return KERN_SUCCESS;
}