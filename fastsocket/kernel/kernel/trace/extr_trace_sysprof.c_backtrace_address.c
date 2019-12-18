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
struct backtrace_info {scalar_t__ pos; int /*<<< orphan*/  data; int /*<<< orphan*/  tr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trace_special (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ sample_max_depth ; 

__attribute__((used)) static void backtrace_address(void *data, unsigned long addr, int reliable)
{
	struct backtrace_info *info = data;

	if (info->pos < sample_max_depth && reliable) {
		__trace_special(info->tr, info->data, 1, addr, 0);

		info->pos++;
	}
}