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
typedef  size_t u8 ;
typedef  int u16 ;
struct antsel_info {scalar_t__ antsel_type; } ;

/* Variables and functions */
 scalar_t__ ANTSEL_2x3 ; 
 scalar_t__ ANTSEL_2x4 ; 
 size_t BRCMS_ANTIDX_11N (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRCMS_ANTSEL_11N (size_t) ; 
 int* mimo_2x3_div_antselpat_tbl ; 
 int* mimo_2x4_div_antselpat_tbl ; 

__attribute__((used)) static u16 brcms_c_antsel_antcfg2antsel(struct antsel_info *asi, u8 ant_cfg)
{
	u8 idx = BRCMS_ANTIDX_11N(BRCMS_ANTSEL_11N(ant_cfg));
	u16 mimo_antsel = 0;

	if (asi->antsel_type == ANTSEL_2x4) {
		/* 2x4 antenna diversity board, 4 cfgs: 0-2 0-3 1-2 1-3 */
		mimo_antsel = (mimo_2x4_div_antselpat_tbl[idx] & 0xf);
		return mimo_antsel;

	} else if (asi->antsel_type == ANTSEL_2x3) {
		/* 2x3 antenna selection, 3 cfgs: 0-1 0-2 2-1 */
		mimo_antsel = (mimo_2x3_div_antselpat_tbl[idx] & 0xf);
		return mimo_antsel;
	}

	return mimo_antsel;
}