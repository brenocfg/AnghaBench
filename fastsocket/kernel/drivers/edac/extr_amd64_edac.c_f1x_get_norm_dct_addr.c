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
typedef  int u64 ;
typedef  int u32 ;
struct amd64_pvt {int dct_sel_hi; } ;

/* Variables and functions */
 int BIT_64 (int) ; 
 int GENMASK (int,int) ; 
 int dhar_base (struct amd64_pvt*) ; 
 scalar_t__ dhar_valid (struct amd64_pvt*) ; 
 int f10_dhar_offset (struct amd64_pvt*) ; 
 int get_dram_base (struct amd64_pvt*,unsigned int) ; 

__attribute__((used)) static u64 f1x_get_norm_dct_addr(struct amd64_pvt *pvt, unsigned range,
				 u64 sys_addr, bool hi_rng,
				 u32 dct_sel_base_addr)
{
	u64 chan_off;
	u64 dram_base		= get_dram_base(pvt, range);
	u64 hole_off		= f10_dhar_offset(pvt);
	u64 dct_sel_base_off	= (pvt->dct_sel_hi & 0xFFFFFC00) << 16;

	if (hi_rng) {
		/*
		 * if
		 * base address of high range is below 4Gb
		 * (bits [47:27] at [31:11])
		 * DRAM address space on this DCT is hoisted above 4Gb	&&
		 * sys_addr > 4Gb
		 *
		 *	remove hole offset from sys_addr
		 * else
		 *	remove high range offset from sys_addr
		 */
		if ((!(dct_sel_base_addr >> 16) ||
		     dct_sel_base_addr < dhar_base(pvt)) &&
		    dhar_valid(pvt) &&
		    (sys_addr >= BIT_64(32)))
			chan_off = hole_off;
		else
			chan_off = dct_sel_base_off;
	} else {
		/*
		 * if
		 * we have a valid hole		&&
		 * sys_addr > 4Gb
		 *
		 *	remove hole
		 * else
		 *	remove dram base to normalize to DCT address
		 */
		if (dhar_valid(pvt) && (sys_addr >= BIT_64(32)))
			chan_off = hole_off;
		else
			chan_off = dram_base;
	}

	return (sys_addr & GENMASK(6,47)) - (chan_off & GENMASK(23,47));
}