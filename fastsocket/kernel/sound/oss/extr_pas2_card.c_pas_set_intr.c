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
 int pas_intr_mask ; 
 int /*<<< orphan*/  pas_write (int,int) ; 

int pas_set_intr(int mask)
{
	if (!mask)
		return 0;

	pas_intr_mask |= mask;

	pas_write(pas_intr_mask, 0x0B8B);
	return 0;
}