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
struct TYPE_2__ {scalar_t__ eph_panic_log_offset; scalar_t__ eph_panic_log_len; scalar_t__ eph_other_log_offset; scalar_t__ eph_other_log_len; scalar_t__ eph_stackshot_offset; scalar_t__ eph_stackshot_len; int /*<<< orphan*/  eph_panic_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMBEDDED_PANIC_HEADER_FLAG_NESTED_PANIC ; 
 void* PE_get_offset_into_panic_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PE_init_panicheader () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug_buf_ptr ; 
 TYPE_1__* panic_info ; 

void
PE_update_panicheader_nestedpanic()
{
	if (!panic_info)
		return;

	/*
	 * If the panic log offset is not set, re-init the panic header
	 */
	if (panic_info->eph_panic_log_offset == 0) {
		PE_init_panicheader();
		panic_info->eph_panic_flags |= EMBEDDED_PANIC_HEADER_FLAG_NESTED_PANIC;
		return;
	}

	panic_info->eph_panic_flags |= EMBEDDED_PANIC_HEADER_FLAG_NESTED_PANIC;

	/*
	 * If the panic log length is not set, set the end to
	 * the current location of the debug_buf_ptr to close it.
	 */
	if (panic_info->eph_panic_log_len == 0) {
		panic_info->eph_panic_log_len = PE_get_offset_into_panic_region(debug_buf_ptr);

		/* If this assert fires, it's indicative of corruption in the panic region */
		assert(panic_info->eph_other_log_offset == panic_info->eph_other_log_len == 0);
	}

	/* If this assert fires, it's likely indicative of corruption in the panic region */
	assert(((panic_info->eph_stackshot_offset == 0) && (panic_info->eph_stackshot_len == 0)) ||
			((panic_info->eph_stackshot_offset != 0) && (panic_info->eph_stackshot_len != 0)));

	/*
	 * If we haven't set up the other log yet, set the beginning of the other log
	 * to the current location of the debug_buf_ptr
	 */
	if (panic_info->eph_other_log_offset == 0) {
		panic_info->eph_other_log_offset = PE_get_offset_into_panic_region(debug_buf_ptr);

		/* If this assert fires, it's indicative of corruption in the panic region */
		assert(panic_info->eph_other_log_len == 0);
	}

	return;
}