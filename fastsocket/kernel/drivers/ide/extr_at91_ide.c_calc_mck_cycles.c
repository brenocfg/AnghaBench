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
typedef  unsigned int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned int,int) ; 

__attribute__((used)) static unsigned int calc_mck_cycles(unsigned int ns, unsigned int mck_hz)
{
	u64 tmp = ns;

	tmp *= mck_hz;
	tmp += 1000*1000*1000 - 1; /* round up */
	do_div(tmp, 1000*1000*1000);
	return (unsigned int) tmp;
}