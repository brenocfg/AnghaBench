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
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  ipf_pktopts_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */

__attribute__((used)) static errno_t
ipf_output_detached(void *cookie, mbuf_t *data, ipf_pktopts_t options)
{
#pragma unused(cookie, data, options)

#if DEBUG
	printf("ipf_output_detached\n");
#endif /* DEBUG */

	return (0);
}