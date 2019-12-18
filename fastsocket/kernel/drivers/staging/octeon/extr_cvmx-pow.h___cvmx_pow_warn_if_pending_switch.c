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

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MF_CHORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 

__attribute__((used)) static inline void __cvmx_pow_warn_if_pending_switch(const char *function)
{
	uint64_t switch_complete;
	CVMX_MF_CHORD(switch_complete);
	if (!switch_complete)
		pr_warning("%s called with tag switch in progress\n", function);
}