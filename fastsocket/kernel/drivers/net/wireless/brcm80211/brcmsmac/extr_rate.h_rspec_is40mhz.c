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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ PHY_TXC1_BW_40MHZ ; 
 scalar_t__ PHY_TXC1_BW_40MHZ_DUP ; 
 scalar_t__ rspec_get_bw (scalar_t__) ; 

__attribute__((used)) static inline bool rspec_is40mhz(u32 rspec)
{
	u32 bw = rspec_get_bw(rspec);

	return bw == PHY_TXC1_BW_40MHZ || bw == PHY_TXC1_BW_40MHZ_DUP;
}