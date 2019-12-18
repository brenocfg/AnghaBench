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
typedef  int /*<<< orphan*/  u32 ;
struct aty128fb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_CNTL_DATA ; 
 int /*<<< orphan*/  CLOCK_CNTL_INDEX ; 
 int /*<<< orphan*/  aty_ld_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aty_st_8 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static u32 _aty_ld_pll(unsigned int pll_index,
		       const struct aty128fb_par *par)
{       
	aty_st_8(CLOCK_CNTL_INDEX, pll_index & 0x3F);
	return aty_ld_le32(CLOCK_CNTL_DATA);
}