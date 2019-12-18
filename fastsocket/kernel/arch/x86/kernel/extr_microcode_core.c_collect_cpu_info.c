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
struct ucode_cpu_info {int valid; int /*<<< orphan*/  cpu_sig; } ;

/* Variables and functions */
 int collect_cpu_info_on_target (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ucode_cpu_info*,int /*<<< orphan*/ ,int) ; 
 struct ucode_cpu_info* ucode_cpu_info ; 

__attribute__((used)) static int collect_cpu_info(int cpu)
{
	struct ucode_cpu_info *uci = ucode_cpu_info + cpu;
	int ret;

	memset(uci, 0, sizeof(*uci));

	ret = collect_cpu_info_on_target(cpu, &uci->cpu_sig);
	if (!ret)
		uci->valid = 1;

	return ret;
}