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
 int AT91X40_MASTER_CLOCK ; 
 scalar_t__ AT91_TC ; 
 scalar_t__ AT91_TC_CLK1BASE ; 
 scalar_t__ AT91_TC_CV ; 
 int at91_sys_read (scalar_t__) ; 

__attribute__((used)) static unsigned long at91x40_gettimeoffset(void)
{
	return (at91_sys_read(AT91_TC + AT91_TC_CLK1BASE + AT91_TC_CV) * 1000000 / (AT91X40_MASTER_CLOCK / 128));
}