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
typedef  int /*<<< orphan*/  __get_cpu_var ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCR_PIC_PRIV ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmi_active ; 
 TYPE_1__* pcr_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void stop_nmi_watchdog(void *unused)
{
	pcr_ops->write(PCR_PIC_PRIV);
	__get_cpu_var(wd_enabled) = 0;
	atomic_dec(&nmi_active);
}