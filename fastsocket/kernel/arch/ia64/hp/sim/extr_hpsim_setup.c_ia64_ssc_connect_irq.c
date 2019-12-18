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
 int /*<<< orphan*/  SSC_CONNECT_INTERRUPT ; 
 int /*<<< orphan*/  ia64_ssc (long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ia64_ssc_connect_irq (long intr, long irq)
{
	ia64_ssc(intr, irq, 0, 0, SSC_CONNECT_INTERRUPT);
}