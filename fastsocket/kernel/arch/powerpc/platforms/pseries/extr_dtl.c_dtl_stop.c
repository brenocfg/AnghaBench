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
struct dtl {size_t cpu; } ;
struct TYPE_2__ {int dtl_enable_mask; } ;

/* Variables and functions */
 int get_hard_smp_processor_id (size_t) ; 
 TYPE_1__* lppaca ; 
 int /*<<< orphan*/  unregister_dtl (int) ; 

__attribute__((used)) static void dtl_stop(struct dtl *dtl)
{
	int hwcpu = get_hard_smp_processor_id(dtl->cpu);

	lppaca[dtl->cpu].dtl_enable_mask = 0x0;

	unregister_dtl(hwcpu);
}