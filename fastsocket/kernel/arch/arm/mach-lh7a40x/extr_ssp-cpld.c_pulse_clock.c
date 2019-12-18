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
 int /*<<< orphan*/  CPLD_SPI ; 
 int /*<<< orphan*/  CPLD_SPI_SCLK ; 
 int /*<<< orphan*/  T_SKH ; 
 int /*<<< orphan*/  T_SKL ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulse_clock (void)
{
	CPLD_SPI |=  CPLD_SPI_SCLK;
	udelay (T_SKH);
	CPLD_SPI &= ~CPLD_SPI_SCLK;
	udelay (T_SKL);
}