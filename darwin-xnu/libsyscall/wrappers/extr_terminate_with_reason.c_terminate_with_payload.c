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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int __terminate_with_payload (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
terminate_with_payload(int pid, uint32_t reason_namespace, uint64_t reason_code,
			void *payload, uint32_t payload_size,
                        const char *reason_string, uint64_t reason_flags)
{
	return __terminate_with_payload(pid, reason_namespace, reason_code, payload,
					payload_size, reason_string, reason_flags);
}