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
struct qe_ic {int dummy; } ;
struct TYPE_2__ {struct qe_ic* chip_data; } ;

/* Variables and functions */
 TYPE_1__* irq_desc ; 

__attribute__((used)) static inline struct qe_ic *qe_ic_from_irq(unsigned int virq)
{
	return irq_desc[virq].chip_data;
}