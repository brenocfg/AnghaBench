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
struct TYPE_2__ {int period_ns; unsigned char reg_value; } ;

/* Variables and functions */
 TYPE_1__* sync_xfer_table ; 

__attribute__((used)) static
int acornscsi_getperiod(unsigned char syncxfer)
{
    int i;

    syncxfer &= 0xf0;
    if (syncxfer == 0x10)
	syncxfer = 0;

    for (i = 1; sync_xfer_table[i].period_ns; i++)
	if (syncxfer == sync_xfer_table[i].reg_value)
	    return sync_xfer_table[i].period_ns;
    return 0;
}