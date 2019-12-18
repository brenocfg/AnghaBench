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
typedef  int u16 ;

/* Variables and functions */
 int get_sclk () ; 

__attribute__((used)) static inline u16 bfin_kpad_get_prescale(u32 timescale)
{
	u32 sclk = get_sclk();

	return ((((sclk / 1000) * timescale) / 1024) - 1);
}