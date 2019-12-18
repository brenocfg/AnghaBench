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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {scalar_t__ cpu_type; } ;

/* Variables and functions */
 size_t FPU_TYPE_FLAG_POS ; 
 int /*<<< orphan*/  PA2_0_FPU_FLAG ; 
 int /*<<< orphan*/  ROLEX_EXTEN_FLAG ; 
 int /*<<< orphan*/  TIMEX_EXTEN_FLAG ; 
 TYPE_1__ boot_cpu_data ; 
 scalar_t__ pcxs ; 
 scalar_t__ pcxt ; 
 scalar_t__ pcxt_ ; 
 scalar_t__ pcxu ; 

__attribute__((used)) static void parisc_linux_get_fpu_type(u_int fpregs[])
{
	/* on pa-linux the fpu type is not filled in by the
	 * caller; it is constructed here  
	 */ 
	if (boot_cpu_data.cpu_type == pcxs)
		fpregs[FPU_TYPE_FLAG_POS] = TIMEX_EXTEN_FLAG;
	else if (boot_cpu_data.cpu_type == pcxt ||
	         boot_cpu_data.cpu_type == pcxt_)
		fpregs[FPU_TYPE_FLAG_POS] = ROLEX_EXTEN_FLAG;
	else if (boot_cpu_data.cpu_type >= pcxu)
		fpregs[FPU_TYPE_FLAG_POS] = PA2_0_FPU_FLAG;
}