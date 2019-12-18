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
struct brcms_phy {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int s32 ;

/* Variables and functions */
 int LCN_TEMPSENSE_DEN ; 
 int LCN_TEMPSENSE_OFFSET ; 
 int wlc_lcnphy_tempsense_new (struct brcms_phy*,int) ; 

s8 wlc_lcnphy_tempsense_degree(struct brcms_phy *pi, bool mode)
{
	s32 degree = wlc_lcnphy_tempsense_new(pi, mode);
	degree =
		((degree <<
		  10) + LCN_TEMPSENSE_OFFSET + (LCN_TEMPSENSE_DEN >> 1))
		/ LCN_TEMPSENSE_DEN;
	return (s8) degree;
}