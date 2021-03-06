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
struct ucode_cpu_info {scalar_t__ valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* microcode_fini_cpu ) (int) ;} ;

/* Variables and functions */
 TYPE_1__* microcode_ops ; 
 int /*<<< orphan*/  stub1 (int) ; 
 struct ucode_cpu_info* ucode_cpu_info ; 

__attribute__((used)) static void microcode_fini_cpu(int cpu)
{
	struct ucode_cpu_info *uci = ucode_cpu_info + cpu;

	microcode_ops->microcode_fini_cpu(cpu);
	uci->valid = 0;
}