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
typedef  unsigned long u64 ;

/* Variables and functions */
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  do_div (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long get_sclk () ; 

unsigned long usecs_to_sclk(unsigned long usecs)
{
	u64 tmp = get_sclk() * (u64)usecs;
	do_div(tmp, USEC_PER_SEC);
	return tmp;
}