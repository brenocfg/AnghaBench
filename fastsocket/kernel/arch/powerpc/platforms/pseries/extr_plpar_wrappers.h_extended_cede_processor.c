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
typedef  unsigned long u8 ;

/* Variables and functions */
 long cede_processor () ; 
 unsigned long get_cede_latency_hint () ; 
 int /*<<< orphan*/  set_cede_latency_hint (unsigned long) ; 

__attribute__((used)) static inline long extended_cede_processor(unsigned long latency_hint)
{
	long rc;
	u8 old_latency_hint = get_cede_latency_hint();

	set_cede_latency_hint(latency_hint);
	rc = cede_processor();
	set_cede_latency_hint(old_latency_hint);

	return rc;
}