#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_addr ;
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  timebase ;
struct kcdata_descriptor {int dummy; } ;
typedef  scalar_t__ mach_vm_address_t ;
struct TYPE_10__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ mach_timebase_info_data_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_11__ {size_t kcs_elem_offset; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KCDATA_BUFFER_BEGIN_XNUPOST_CONFIG ; 
 int /*<<< orphan*/  KCDATA_TYPE_TIMEBASE ; 
 int /*<<< orphan*/  KCFLAG_USE_COPYOUT ; 
 scalar_t__ KERN_NO_ACCESS ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSVERSIZE ; 
 TYPE_1__* PE_boot_args () ; 
 int /*<<< orphan*/  STACKSHOT_KCTYPE_BOOTARGS ; 
 int /*<<< orphan*/  STACKSHOT_KCTYPE_OSVERSION ; 
 int /*<<< orphan*/  XNUPOST_KCTYPE_TESTCONFIG ; 
 int /*<<< orphan*/ * bsd_post_tests ; 
 size_t bsd_post_tests_count ; 
 int /*<<< orphan*/  clock_timebase_info (TYPE_1__*) ; 
 scalar_t__ copyout (TYPE_1__*,scalar_t__,size_t) ; 
 TYPE_4__* kc_xnupost_test_def ; 
 int kc_xnupost_test_def_count ; 
 scalar_t__ kcdata_add_type_definition (struct kcdata_descriptor*,int /*<<< orphan*/ ,char*,TYPE_4__*,int) ; 
 scalar_t__ kcdata_get_memory_addr (struct kcdata_descriptor*,int /*<<< orphan*/ ,size_t,scalar_t__*) ; 
 scalar_t__ kcdata_get_memory_addr_for_array (struct kcdata_descriptor*,int /*<<< orphan*/ ,size_t,size_t,scalar_t__*) ; 
 scalar_t__ kcdata_memory_get_used_bytes (struct kcdata_descriptor*) ; 
 scalar_t__ kcdata_memory_static_init (struct kcdata_descriptor*,scalar_t__,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t kcs_get_elem_size (TYPE_4__*) ; 
 int /*<<< orphan*/ * kernel_post_tests ; 
 size_t kernel_post_tests_count ; 
 scalar_t__ strlen (TYPE_1__*) ; 
 TYPE_1__* version ; 
 scalar_t__ xnupost_copyout_test (int /*<<< orphan*/ *,scalar_t__) ; 

int
xnupost_export_testdata(void * outp, uint32_t size, uint32_t * lenp)
{
	struct kcdata_descriptor kcd;
	mach_vm_address_t user_addr        = 0;
	mach_vm_address_t tmp_entry_addr   = 0;
	kern_return_t kret                 = 0;
	uint32_t i                         = 0;
	char kctype_name[32]               = "xnupost_test_config";
	mach_timebase_info_data_t timebase = {0, 0};
	uint32_t length_to_copy            = 0;

#define RET_IF_OP_FAIL                                                                                       \
	do {                                                                                                     \
		if (kret != KERN_SUCCESS) {                                                                          \
			return (kret == KERN_NO_ACCESS) ? EACCES : ((kret == KERN_RESOURCE_SHORTAGE) ? ENOMEM : EINVAL); \
		}                                                                                                    \
	} while (0)

	kret = kcdata_memory_static_init(&kcd, (mach_vm_address_t)outp, KCDATA_BUFFER_BEGIN_XNUPOST_CONFIG, size, KCFLAG_USE_COPYOUT);
	RET_IF_OP_FAIL;

	/* add mach timebase info */
	clock_timebase_info(&timebase);
	kret = kcdata_get_memory_addr(&kcd, KCDATA_TYPE_TIMEBASE, sizeof(timebase), &user_addr);
	RET_IF_OP_FAIL;
	kret = copyout(&timebase, user_addr, sizeof(timebase));
	RET_IF_OP_FAIL;

	/* save boot-args and osversion string */
	length_to_copy = MIN((uint32_t)(strlen(version) + 1), OSVERSIZE);
	kret           = kcdata_get_memory_addr(&kcd, STACKSHOT_KCTYPE_OSVERSION, length_to_copy, &user_addr);
	RET_IF_OP_FAIL;
	kret = copyout(&version[0], user_addr, length_to_copy);
	RET_IF_OP_FAIL;

	length_to_copy = MIN((uint32_t)(strlen(PE_boot_args()) + 1), OSVERSIZE);
	kret           = kcdata_get_memory_addr(&kcd, STACKSHOT_KCTYPE_BOOTARGS, length_to_copy, &user_addr);
	RET_IF_OP_FAIL;
	kret = copyout(PE_boot_args(), user_addr, length_to_copy);
	RET_IF_OP_FAIL;

	/* add type definition to buffer */
	kret = kcdata_add_type_definition(&kcd, XNUPOST_KCTYPE_TESTCONFIG, kctype_name, &kc_xnupost_test_def[0],
	                                  kc_xnupost_test_def_count);
	RET_IF_OP_FAIL;

	/* add the tests to buffer as array */
	uint32_t total_tests = bsd_post_tests_count + kernel_post_tests_count;
	uint32_t elem_size = kc_xnupost_test_def[kc_xnupost_test_def_count - 1].kcs_elem_offset +
	                     kcs_get_elem_size(&kc_xnupost_test_def[kc_xnupost_test_def_count - 1]);

	kret = kcdata_get_memory_addr_for_array(&kcd, XNUPOST_KCTYPE_TESTCONFIG, elem_size, total_tests, &user_addr);
	RET_IF_OP_FAIL;

	for (i = 0; i < bsd_post_tests_count; i++) {
		tmp_entry_addr = (mach_vm_address_t)((uint64_t)(user_addr) + (uint64_t)(i * elem_size));
		kret           = xnupost_copyout_test(&bsd_post_tests[i], tmp_entry_addr);
		RET_IF_OP_FAIL;
	}
	user_addr = (mach_vm_address_t)((uint64_t)(user_addr) + (uint64_t)(i * elem_size));

	for (i = 0; i < kernel_post_tests_count; i++) {
		tmp_entry_addr = (mach_vm_address_t)((uint64_t)(user_addr) + (uint64_t)(i * elem_size));
		kret           = xnupost_copyout_test(&kernel_post_tests[i], tmp_entry_addr);
		RET_IF_OP_FAIL;
	}

	if (kret == KERN_SUCCESS && lenp != NULL)
		*lenp = (uint32_t)kcdata_memory_get_used_bytes(&kcd);
	RET_IF_OP_FAIL;

#undef RET_IF_OP_FAIL
	return kret;
}