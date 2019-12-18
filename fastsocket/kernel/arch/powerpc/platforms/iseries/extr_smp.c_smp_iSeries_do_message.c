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
 int /*<<< orphan*/  HvCall_sendIPI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iSeries_smp_message ; 
 int /*<<< orphan*/ * paca ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void smp_iSeries_do_message(int cpu, int msg)
{
	set_bit(msg, &iSeries_smp_message[cpu]);
	HvCall_sendIPI(&(paca[cpu]));
}