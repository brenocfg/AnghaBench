#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* tdt; } ;
struct TYPE_3__ {int fdt; } ;

/* Variables and functions */
 TYPE_2__* bcom_eng ; 

__attribute__((used)) static inline void
bcom_set_task_pragma(int task, int pragma)
{
	u32 *fdt = &bcom_eng->tdt[task].fdt;
	*fdt = (*fdt & ~0xff) | pragma;
}