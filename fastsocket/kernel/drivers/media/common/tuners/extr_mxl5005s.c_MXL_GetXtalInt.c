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

__attribute__((used)) static u32 MXL_GetXtalInt(u32 Xtal_Freq)
{
	if ((Xtal_Freq % 1000000) == 0)
		return (Xtal_Freq / 10000);
	else
		return (((Xtal_Freq / 1000000) + 1)*100);
}