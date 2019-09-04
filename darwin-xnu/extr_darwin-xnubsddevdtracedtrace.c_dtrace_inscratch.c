#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {uintptr_t dtms_scratch_base; uintptr_t dtms_scratch_ptr; } ;
typedef  TYPE_1__ dtrace_mstate_t ;

/* Variables and functions */

__attribute__((used)) static int
dtrace_inscratch(uintptr_t dest, size_t size, dtrace_mstate_t *mstate)
{
	if (dest < mstate->dtms_scratch_base)
		return (0);

	if (dest + size < dest)
		return (0);

	if (dest + size > mstate->dtms_scratch_ptr)
		return (0);

	return (1);
}