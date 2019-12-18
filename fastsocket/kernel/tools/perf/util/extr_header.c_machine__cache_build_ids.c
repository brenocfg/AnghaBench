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
struct machine {int /*<<< orphan*/  user_dsos; int /*<<< orphan*/  kernel_dsos; } ;

/* Variables and functions */
 int __dsos__cache_build_ids (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int machine__cache_build_ids(struct machine *machine, const char *debugdir)
{
	int ret = __dsos__cache_build_ids(&machine->kernel_dsos, debugdir);
	ret |= __dsos__cache_build_ids(&machine->user_dsos, debugdir);
	return ret;
}