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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ DCR6 ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void update_cr6(u32 cr6_data, unsigned long ioaddr)
{
	u32 cr6_tmp;

	cr6_tmp = cr6_data & ~0x2002;           /* stop Tx/Rx */
	outl(cr6_tmp, ioaddr + DCR6);
	udelay(5);
	outl(cr6_data, ioaddr + DCR6);
	udelay(5);
}