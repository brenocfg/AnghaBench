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
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 

__attribute__((used)) static void s3c_irq_demux_timer(unsigned int base_irq, unsigned int sub_irq)
{
	generic_handle_irq(sub_irq);
}