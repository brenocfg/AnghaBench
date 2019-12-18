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
struct parport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  crb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIA_C1_ENABLE_IRQ ; 
 TYPE_1__* pia (struct parport*) ; 

__attribute__((used)) static void mfc3_disable_irq(struct parport *p)
{
	pia(p)->crb &= ~PIA_C1_ENABLE_IRQ;
}