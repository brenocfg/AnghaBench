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
struct TYPE_2__ {unsigned int reg_value; } ;

/* Variables and functions */
 unsigned int SDTR_SIZE ; 
 size_t round_period (unsigned int) ; 
 TYPE_1__* sync_xfer_table ; 

__attribute__((used)) static
unsigned char calc_sync_xfer(unsigned int period, unsigned int offset)
{
    return sync_xfer_table[round_period(period)].reg_value |
		((offset < SDTR_SIZE) ? offset : SDTR_SIZE);
}