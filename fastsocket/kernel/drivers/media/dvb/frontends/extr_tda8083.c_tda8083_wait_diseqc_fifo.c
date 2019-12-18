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
struct tda8083_state {int dummy; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int tda8083_readreg (struct tda8083_state*,int) ; 

__attribute__((used)) static void tda8083_wait_diseqc_fifo (struct tda8083_state* state, int timeout)
{
	unsigned long start = jiffies;

	while (jiffies - start < timeout &&
	       !(tda8083_readreg(state, 0x02) & 0x80))
	{
		msleep(50);
	};
}