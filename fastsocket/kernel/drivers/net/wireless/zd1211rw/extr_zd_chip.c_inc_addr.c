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
typedef  int /*<<< orphan*/  zd_addr_t ;
typedef  int u16 ;

/* Variables and functions */
 int CR_START ; 

__attribute__((used)) static zd_addr_t inc_addr(zd_addr_t addr)
{
	u16 a = (u16)addr;
	/* Control registers use byte addressing, but everything else uses word
	 * addressing. */
	if ((a & 0xf000) == CR_START)
		a += 2;
	else
		a += 1;
	return (zd_addr_t)a;
}