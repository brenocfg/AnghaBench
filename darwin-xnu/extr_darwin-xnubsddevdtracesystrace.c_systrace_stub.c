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
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */

void
systrace_stub(dtrace_id_t id, uint64_t arg0, uint64_t arg1,
    uint64_t arg2, uint64_t arg3, uint64_t arg4)
{
#pragma unused(id,arg0,arg1,arg2,arg3,arg4)
}