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
 scalar_t__ SDCPWR_CFGA0_REG ; 
 int in_le32 (scalar_t__) ; 
 scalar_t__ sdcpwr_mapbase ; 

__attribute__((used)) static int get_astate_freq(int astate)
{
	u32 ret;
	ret = in_le32(sdcpwr_mapbase + SDCPWR_CFGA0_REG + (astate * 0x10));

	return ret & 0x3f;
}