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
typedef  int uint64_t ;
struct _uint64_with_description_data {int data; int /*<<< orphan*/ * desc; } ;
typedef  int /*<<< orphan*/  save_data ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_1__* kcdata_descriptor_t ;
struct TYPE_4__ {int kcd_flags; } ;

/* Variables and functions */
 scalar_t__ KCDATA_DESC_MAXLEN ; 
 int /*<<< orphan*/  KCDATA_TYPE_UINT64_DESC ; 
 int KCFLAG_USE_COPYOUT ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_NO_ACCESS ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  bzero (struct _uint64_with_description_data*,int const) ; 
 scalar_t__ copyout (struct _uint64_with_description_data*,scalar_t__,int const) ; 
 scalar_t__ kcdata_get_memory_addr (TYPE_1__*,int /*<<< orphan*/ ,int const,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (void*,struct _uint64_with_description_data*,int const) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 

kern_return_t
kcdata_add_uint64_with_description(kcdata_descriptor_t data_desc, uint64_t data, const char * description)
{
	if (strlen(description) >= KCDATA_DESC_MAXLEN)
		return KERN_INVALID_ARGUMENT;

	kern_return_t kr = 0;
	mach_vm_address_t user_addr;
	struct _uint64_with_description_data save_data;
	const uint64_t size_req = sizeof(save_data);
	bzero(&save_data, size_req);

	strlcpy(&(save_data.desc[0]), description, sizeof(save_data.desc));
	save_data.data = data;

	kr = kcdata_get_memory_addr(data_desc, KCDATA_TYPE_UINT64_DESC, size_req, &user_addr);
	if (kr != KERN_SUCCESS)
		return kr;

	if (data_desc->kcd_flags & KCFLAG_USE_COPYOUT) {
		if (copyout(&save_data, user_addr, size_req))
			return KERN_NO_ACCESS;
	} else {
		memcpy((void *)user_addr, &save_data, size_req);
	}
	return KERN_SUCCESS;
}