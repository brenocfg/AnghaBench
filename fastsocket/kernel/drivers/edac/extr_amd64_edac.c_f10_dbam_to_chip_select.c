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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct amd64_pvt {int dclr1; int dclr0; int dchr0; int dchr1; } ;

/* Variables and functions */
 int DDR3_MODE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WIDTH_128 ; 
 int ddr2_cs_size (unsigned int,int) ; 
 int ddr3_cs_size (unsigned int,int) ; 

__attribute__((used)) static int f10_dbam_to_chip_select(struct amd64_pvt *pvt, u8 dct,
				   unsigned cs_mode)
{
	u32 dclr = dct ? pvt->dclr1 : pvt->dclr0;

	WARN_ON(cs_mode > 11);

	if (pvt->dchr0 & DDR3_MODE || pvt->dchr1 & DDR3_MODE)
		return ddr3_cs_size(cs_mode, dclr & WIDTH_128);
	else
		return ddr2_cs_size(cs_mode, dclr & WIDTH_128);
}