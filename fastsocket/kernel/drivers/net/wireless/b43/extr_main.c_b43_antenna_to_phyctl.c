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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
#define  B43_ANTENNA0 133 
#define  B43_ANTENNA1 132 
#define  B43_ANTENNA2 131 
#define  B43_ANTENNA3 130 
#define  B43_ANTENNA_AUTO0 129 
#define  B43_ANTENNA_AUTO1 128 
 int /*<<< orphan*/  B43_TXH_PHY_ANT0 ; 
 int /*<<< orphan*/  B43_TXH_PHY_ANT01AUTO ; 
 int /*<<< orphan*/  B43_TXH_PHY_ANT1 ; 
 int /*<<< orphan*/  B43_TXH_PHY_ANT2 ; 
 int /*<<< orphan*/  B43_TXH_PHY_ANT3 ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 

__attribute__((used)) static u16 b43_antenna_to_phyctl(int antenna)
{
	switch (antenna) {
	case B43_ANTENNA0:
		return B43_TXH_PHY_ANT0;
	case B43_ANTENNA1:
		return B43_TXH_PHY_ANT1;
	case B43_ANTENNA2:
		return B43_TXH_PHY_ANT2;
	case B43_ANTENNA3:
		return B43_TXH_PHY_ANT3;
	case B43_ANTENNA_AUTO0:
	case B43_ANTENNA_AUTO1:
		return B43_TXH_PHY_ANT01AUTO;
	}
	B43_WARN_ON(1);
	return 0;
}