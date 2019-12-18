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
typedef  int const u32 ;

/* Variables and functions */
 int SCC_UHC_USBCEN ; 

__attribute__((used)) static inline int uhc_clkctrl_ready(u32 val)
{
	const u32 mask = SCC_UHC_USBCEN | SCC_UHC_USBCEN;
	return((val & mask) == mask);
}