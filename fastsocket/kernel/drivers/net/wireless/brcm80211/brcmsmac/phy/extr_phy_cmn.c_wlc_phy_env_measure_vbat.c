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

/* Variables and functions */
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_vbatsense (struct brcms_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s8 wlc_phy_env_measure_vbat(struct brcms_phy *pi)
{
	if (ISLCNPHY(pi))
		return wlc_lcnphy_vbatsense(pi, 0);
	else
		return 0;
}