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
typedef  TYPE_1__* os_reason_t ;
typedef  int /*<<< orphan*/  kcdata_iter_t ;
struct TYPE_4__ {scalar_t__ osr_bufsize; int /*<<< orphan*/ * osr_kcd_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_REASON_USER_DESC ; 
 scalar_t__ KCDATA_BUFFER_BEGIN_OS_REASON ; 
 TYPE_1__* OS_REASON_NULL ; 
 int /*<<< orphan*/  kcdata_iter (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kcdata_iter_find_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kcdata_iter_payload (int /*<<< orphan*/ ) ; 
 int kcdata_iter_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcdata_iter_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

char *
launchd_exit_reason_get_string_desc(os_reason_t exit_reason)
{
	kcdata_iter_t iter;

	if (exit_reason == OS_REASON_NULL || exit_reason->osr_kcd_buf == NULL ||
			exit_reason->osr_bufsize == 0) {
		return NULL;
	}

	iter = kcdata_iter(exit_reason->osr_kcd_buf, exit_reason->osr_bufsize);
	if (!kcdata_iter_valid(iter)) {
#if DEBUG || DEVELOPMENT
		printf("launchd exit reason has invalid exit reason buffer\n");
#endif
		return NULL;
	}

	if (kcdata_iter_type(iter) != KCDATA_BUFFER_BEGIN_OS_REASON) {
#if DEBUG || DEVELOPMENT
		printf("launchd exit reason buffer type mismatch, expected %d got %d\n",
			KCDATA_BUFFER_BEGIN_OS_REASON, kcdata_iter_type(iter));
#endif
		return NULL;
	}

	iter = kcdata_iter_find_type(iter, EXIT_REASON_USER_DESC);
	if (!kcdata_iter_valid(iter)) {
		return NULL;
	}

	return (char *)kcdata_iter_payload(iter);
}