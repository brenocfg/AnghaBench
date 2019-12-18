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
struct mite_struct {TYPE_1__* pcidev; } ;
struct TYPE_2__ {unsigned int irq; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int mite_irq(struct mite_struct *mite)
{
	return mite->pcidev->irq;
}