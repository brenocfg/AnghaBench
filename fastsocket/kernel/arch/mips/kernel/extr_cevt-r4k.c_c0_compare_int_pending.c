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
 int cp0_compare_irq ; 
 int read_c0_cause () ; 

__attribute__((used)) static int c0_compare_int_pending(void)
{
	return (read_c0_cause() >> cp0_compare_irq) & 0x100;
}