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
typedef  int /*<<< orphan*/  uint ;
typedef  size_t u8 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rate_20; int /*<<< orphan*/  phy_rate_40; int /*<<< orphan*/  phy_rate_20_sgi; int /*<<< orphan*/  phy_rate_40_sgi; } ;

/* Variables and functions */
 TYPE_1__* mcs_table ; 

__attribute__((used)) static inline uint mcs_2_rate(u8 mcs, bool is40, bool sgi)
{
	if (sgi) {
		if (is40)
			return mcs_table[mcs].phy_rate_40_sgi;
		return mcs_table[mcs].phy_rate_20_sgi;
	}
	if (is40)
		return mcs_table[mcs].phy_rate_40;

	return mcs_table[mcs].phy_rate_20;
}