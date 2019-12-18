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
struct ctlr_info {TYPE_1__* pdev; scalar_t__ vaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long SA5_INTR_PENDING ; 
 scalar_t__ SA5_INTR_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static bool SA5_intr_pending(struct ctlr_info *h)
{
	unsigned long register_value  =
		readl(h->vaddr + SA5_INTR_STATUS);
	dev_dbg(&h->pdev->dev, "intr_pending %lx\n", register_value);
	return register_value & SA5_INTR_PENDING;
}