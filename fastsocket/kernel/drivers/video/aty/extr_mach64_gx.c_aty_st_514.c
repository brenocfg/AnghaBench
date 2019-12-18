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
struct atyfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_CNTL ; 
 int /*<<< orphan*/  DAC_DATA ; 
 int /*<<< orphan*/  DAC_MASK ; 
 int /*<<< orphan*/  DAC_W_INDEX ; 
 int /*<<< orphan*/  aty_st_8 (int /*<<< orphan*/ ,int,struct atyfb_par const*) ; 

__attribute__((used)) static void aty_st_514(int offset, u8 val, const struct atyfb_par *par)
{
	aty_st_8(DAC_CNTL, 1, par);
	/* right addr byte */
	aty_st_8(DAC_W_INDEX, offset & 0xff, par);
	/* left addr byte */
	aty_st_8(DAC_DATA, (offset >> 8) & 0xff, par);
	aty_st_8(DAC_MASK, val, par);
	aty_st_8(DAC_CNTL, 0, par);
}