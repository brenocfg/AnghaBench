#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int try_vmlinux_path; int sort_by_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 
 int symbol__init () ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int init_user_exec(void)
{
	int ret = 0;

	symbol_conf.try_vmlinux_path = false;
	symbol_conf.sort_by_name = true;
	ret = symbol__init();

	if (ret < 0)
		pr_debug("Failed to init symbol map.\n");

	return ret;
}