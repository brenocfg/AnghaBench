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
 int spi_ll_master_cal_clock (int,int,int,int /*<<< orphan*/ *) ; 

int spi_hal_master_cal_clock(int fapb, int hz, int duty_cycle)
{
    return spi_ll_master_cal_clock(fapb, hz, duty_cycle, NULL);
}