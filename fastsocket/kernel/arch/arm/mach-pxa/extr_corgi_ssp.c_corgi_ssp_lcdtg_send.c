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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  corgi_ssp_dac_put (int) ; 

void corgi_ssp_lcdtg_send(u8 adrs, u8 data)
{
	corgi_ssp_dac_put(((adrs & 0x07) << 5) | (data & 0x1f));
}