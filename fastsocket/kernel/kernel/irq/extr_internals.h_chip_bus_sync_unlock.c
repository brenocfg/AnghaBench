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
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bus_sync_unlock ) (unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/  (*) (unsigned int)) ; 

__attribute__((used)) static inline void chip_bus_sync_unlock(unsigned int irq, struct irq_desc *desc)
{
	if (unlikely(desc->chip->bus_sync_unlock))
		desc->chip->bus_sync_unlock(irq);
}