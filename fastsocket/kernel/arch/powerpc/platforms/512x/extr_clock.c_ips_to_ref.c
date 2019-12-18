#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int scfr1; } ;

/* Variables and functions */
 TYPE_1__* clockctl ; 
 long sys_to_ref (unsigned long) ; 

__attribute__((used)) static long ips_to_ref(unsigned long rate)
{
	int ips_div = (clockctl->scfr1 >> 23) & 0x7;

	rate *= ips_div;	/* csb_clk = ips_clk * ips_div */
	rate *= 2;		/* sys_clk = csb_clk * 2 */
	return sys_to_ref(rate);
}