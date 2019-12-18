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
typedef  union ns_mem {int dummy; } ns_mem ;
struct TYPE_2__ {size_t row; } ;
struct nandsim {TYPE_1__ regs; union ns_mem* pages; } ;

/* Variables and functions */

__attribute__((used)) static inline union ns_mem *NS_GET_PAGE(struct nandsim *ns)
{
	return &(ns->pages[ns->regs.row]);
}