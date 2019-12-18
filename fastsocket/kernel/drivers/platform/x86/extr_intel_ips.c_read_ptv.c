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
typedef  int u16 ;
struct ips_driver {int pta_val; } ;

/* Variables and functions */
 int PTA_OFFSET_MASK ; 
 int PTA_SLOPE_MASK ; 
 int PTA_SLOPE_SHIFT ; 
 int PTV_MASK ; 
 int /*<<< orphan*/  THM_PTV ; 
 int thm_readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 read_ptv(struct ips_driver *ips)
{
	u16 val, slope, offset;

	slope = (ips->pta_val & PTA_SLOPE_MASK) >> PTA_SLOPE_SHIFT;
	offset = ips->pta_val & PTA_OFFSET_MASK;

	val = thm_readw(THM_PTV) & PTV_MASK;

	return val;
}