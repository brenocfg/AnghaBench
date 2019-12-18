#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ampdu_info {TYPE_1__* wlc; } ;
struct TYPE_2__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 scalar_t__ BRCMS_PHY_11N_CAP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool brcms_c_ampdu_cap(struct ampdu_info *ampdu)
{
	if (BRCMS_PHY_11N_CAP(ampdu->wlc->band))
		return true;
	else
		return false;
}