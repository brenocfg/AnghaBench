#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_addr_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* os_reason_t ;
typedef  scalar_t__ mach_vm_address_t ;
struct TYPE_6__ {int osr_flags; int /*<<< orphan*/  osr_kcd_descriptor; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int EXIT_REASON_PAYLOAD_MAX_LEN ; 
 int /*<<< orphan*/  EXIT_REASON_USER_DESC ; 
 int EXIT_REASON_USER_DESC_MAX_LEN ; 
 int /*<<< orphan*/  EXIT_REASON_USER_PAYLOAD ; 
 scalar_t__ KERN_SUCCESS ; 
 int OS_REASON_FLAG_BAD_PARAMS ; 
 int OS_REASON_FLAG_FAILED_DATA_COPYIN ; 
 int OS_REASON_FLAG_FROM_USERSPACE ; 
 int OS_REASON_FLAG_GENERATE_CRASH_REPORT ; 
 int OS_REASON_FLAG_MASK_ALLOWED_FROM_USER ; 
 int OS_REASON_FLAG_NO_CRASH_REPORT ; 
 int OS_REASON_FLAG_PAYLOAD_TRUNCATED ; 
 TYPE_1__* OS_REASON_NULL ; 
 scalar_t__ USER_ADDR_NULL ; 
 int copyin (scalar_t__,void*,int) ; 
 int copyinstr (scalar_t__,void*,int,size_t*) ; 
 scalar_t__ kalloc (int) ; 
 int kcdata_estimate_required_buffer_size (int,int) ; 
 scalar_t__ kcdata_get_memory_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  kcdata_memcpy (int /*<<< orphan*/ *,scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  kfree (char*,int) ; 
 int os_reason_alloc_buffer (TYPE_1__*,int) ; 
 TYPE_1__* os_reason_create (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

os_reason_t
build_userspace_exit_reason(uint32_t reason_namespace, uint64_t reason_code, user_addr_t payload, uint32_t payload_size,
					user_addr_t reason_string, uint64_t reason_flags)
{
	os_reason_t exit_reason = OS_REASON_NULL;

	int error = 0;
	int num_items_to_copy = 0;
	uint32_t user_data_to_copy = 0;
	char *reason_user_desc = NULL;
	size_t reason_user_desc_len = 0;

	exit_reason = os_reason_create(reason_namespace, reason_code);
	if (exit_reason == OS_REASON_NULL) {
		printf("build_userspace_exit_reason: failed to allocate exit reason\n");
		return exit_reason;
	}

	exit_reason->osr_flags |= OS_REASON_FLAG_FROM_USERSPACE;

	/*
	 * Only apply flags that are allowed to be passed from userspace.
	 */
	exit_reason->osr_flags |= (reason_flags & OS_REASON_FLAG_MASK_ALLOWED_FROM_USER);
	if ((reason_flags & OS_REASON_FLAG_MASK_ALLOWED_FROM_USER) != reason_flags) {
		printf("build_userspace_exit_reason: illegal flags passed from userspace (some masked off) 0x%llx, ns: %u, code 0x%llx\n",
			reason_flags, reason_namespace, reason_code);
	}

	if (!(exit_reason->osr_flags & OS_REASON_FLAG_NO_CRASH_REPORT)) {
		exit_reason->osr_flags |= OS_REASON_FLAG_GENERATE_CRASH_REPORT;
	}

	if (payload != USER_ADDR_NULL) {
		if (payload_size == 0) {
			printf("build_userspace_exit_reason: exit reason with namespace %u, nonzero payload but zero length\n",
					reason_namespace);
			exit_reason->osr_flags |= OS_REASON_FLAG_BAD_PARAMS;
			payload = USER_ADDR_NULL;
		} else {
			num_items_to_copy++;

			if (payload_size > EXIT_REASON_PAYLOAD_MAX_LEN) {
				exit_reason->osr_flags |= OS_REASON_FLAG_PAYLOAD_TRUNCATED;
				payload_size = EXIT_REASON_PAYLOAD_MAX_LEN;
			}

			user_data_to_copy += payload_size;
		}
	}

	if (reason_string != USER_ADDR_NULL) {
		reason_user_desc = (char *) kalloc(EXIT_REASON_USER_DESC_MAX_LEN);

		if (reason_user_desc != NULL) {
			error = copyinstr(reason_string, (void *) reason_user_desc,
						EXIT_REASON_USER_DESC_MAX_LEN, &reason_user_desc_len);

			if (error == 0) {
				num_items_to_copy++;
				user_data_to_copy += reason_user_desc_len;
			} else if (error == ENAMETOOLONG) {
				num_items_to_copy++;
				reason_user_desc[EXIT_REASON_USER_DESC_MAX_LEN - 1] = '\0';
				user_data_to_copy += reason_user_desc_len;
			} else {
				exit_reason->osr_flags |= OS_REASON_FLAG_FAILED_DATA_COPYIN;
				kfree(reason_user_desc, EXIT_REASON_USER_DESC_MAX_LEN);
				reason_user_desc = NULL;
				reason_user_desc_len = 0;
			}
		}
	}

	if (num_items_to_copy != 0) {
		uint32_t reason_buffer_size_estimate = 0;
		mach_vm_address_t data_addr = 0;

		reason_buffer_size_estimate = kcdata_estimate_required_buffer_size(num_items_to_copy, user_data_to_copy);

		error = os_reason_alloc_buffer(exit_reason, reason_buffer_size_estimate);
		if (error != 0) {
			printf("build_userspace_exit_reason: failed to allocate signal reason buffer\n");
			goto out_failed_copyin;
		}

		if (reason_user_desc != NULL && reason_user_desc_len != 0) {
			if (KERN_SUCCESS == kcdata_get_memory_addr(&exit_reason->osr_kcd_descriptor,
						EXIT_REASON_USER_DESC,
						reason_user_desc_len,
						&data_addr)) {

				kcdata_memcpy(&exit_reason->osr_kcd_descriptor, (mach_vm_address_t) data_addr,
						reason_user_desc, reason_user_desc_len);
			} else {
				printf("build_userspace_exit_reason: failed to allocate space for reason string\n");
				goto out_failed_copyin;
			}
		}

		if (payload != USER_ADDR_NULL) {
			if (KERN_SUCCESS ==
					kcdata_get_memory_addr(&exit_reason->osr_kcd_descriptor,
						EXIT_REASON_USER_PAYLOAD,
						payload_size,
						&data_addr)) {
				error = copyin(payload, (void *) data_addr, payload_size);
				if (error) {
					printf("build_userspace_exit_reason: failed to copy in payload data with error %d\n", error);
					goto out_failed_copyin;
				}
			} else {
				printf("build_userspace_exit_reason: failed to allocate space for payload data\n");
				goto out_failed_copyin;
			}
		}
	}

	if (reason_user_desc != NULL) {
		kfree(reason_user_desc, EXIT_REASON_USER_DESC_MAX_LEN);
		reason_user_desc = NULL;
		reason_user_desc_len = 0;
	}

	return exit_reason;

out_failed_copyin:

	if (reason_user_desc != NULL) {
		kfree(reason_user_desc, EXIT_REASON_USER_DESC_MAX_LEN);
		reason_user_desc = NULL;
		reason_user_desc_len = 0;
	}

	exit_reason->osr_flags |= OS_REASON_FLAG_FAILED_DATA_COPYIN;
	os_reason_alloc_buffer(exit_reason, 0);
	return exit_reason;
}