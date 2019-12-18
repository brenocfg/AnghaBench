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
 unsigned long USEC_PER_SEC ; 
 int /*<<< orphan*/  do_div (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_sclk () ; 

unsigned long sclk_to_usecs(unsigned long sclk)
{
	u64 tmp = USEC_PER_SEC * (u64)sclk;
	do_div(tmp, get_sclk());
	return tmp;
}