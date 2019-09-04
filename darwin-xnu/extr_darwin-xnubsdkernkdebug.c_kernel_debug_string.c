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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  str_buf ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_STR_LEN ; 
 int STR_BUF_SIZE ; 
 scalar_t__ __probable (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int kdebug_check_trace_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdebug_current_proc_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdebug_debugid_enabled (int /*<<< orphan*/ ) ; 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  kernel_debug_string_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  static_assert (int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

int
kernel_debug_string(uint32_t debugid, uint64_t *str_id, const char *str)
{
	/* arguments to tracepoints must be word-aligned */
	__attribute__((aligned(sizeof(uintptr_t)))) char str_buf[STR_BUF_SIZE];
	static_assert(sizeof(str_buf) > MAX_STR_LEN);
	vm_size_t len_copied;
	int err;

	assert(str_id);

	if (__probable(kdebug_enable == 0)) {
		return 0;
	}

	if (!kdebug_current_proc_enabled(debugid)) {
		return 0;
	}

	if (!kdebug_debugid_enabled(debugid)) {
		return 0;
	}

	if ((err = kdebug_check_trace_string(debugid, *str_id)) != 0) {
		return err;
	}

	if (str == NULL) {
		if (str_id == 0) {
			return EINVAL;
		}

		*str_id = kernel_debug_string_internal(debugid, *str_id, NULL, 0);
		return 0;
	}

	memset(str_buf, 0, sizeof(str_buf));
	len_copied = strlcpy(str_buf, str, MAX_STR_LEN + 1);
	*str_id = kernel_debug_string_internal(debugid, *str_id, str_buf,
	                                       len_copied);
	return 0;
}