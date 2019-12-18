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
 int /*<<< orphan*/  SOFTIRQ_DISABLE_OFFSET ; 
 int /*<<< orphan*/  __local_bh_enable (int /*<<< orphan*/ ) ; 

void _local_bh_enable(void)
{
	__local_bh_enable(SOFTIRQ_DISABLE_OFFSET);
}