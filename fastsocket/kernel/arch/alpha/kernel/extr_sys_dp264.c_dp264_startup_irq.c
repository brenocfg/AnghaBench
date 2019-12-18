#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  dp264_enable_irq (unsigned int) ; 

__attribute__((used)) static unsigned int
dp264_startup_irq(unsigned int irq)
{ 
	dp264_enable_irq(irq);
	return 0; /* never anything pending */
}