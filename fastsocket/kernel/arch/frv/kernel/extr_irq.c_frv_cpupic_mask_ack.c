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
 int /*<<< orphan*/  __clr_IRL () ; 
 int /*<<< orphan*/  __clr_RC (unsigned int) ; 
 int /*<<< orphan*/  __set_MASK (unsigned int) ; 

__attribute__((used)) static void frv_cpupic_mask_ack(unsigned int irqlevel)
{
	__set_MASK(irqlevel);
	__clr_RC(irqlevel);
	__clr_IRL();
}