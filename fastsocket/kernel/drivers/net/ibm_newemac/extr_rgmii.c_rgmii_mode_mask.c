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

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  PHY_MODE_GMII 132 
#define  PHY_MODE_MII 131 
#define  PHY_MODE_RGMII 130 
#define  PHY_MODE_RTBI 129 
#define  PHY_MODE_TBI 128 
 int /*<<< orphan*/  RGMII_FER_GMII (int) ; 
 int /*<<< orphan*/  RGMII_FER_MII (int) ; 
 int /*<<< orphan*/  RGMII_FER_RGMII (int) ; 
 int /*<<< orphan*/  RGMII_FER_RTBI (int) ; 
 int /*<<< orphan*/  RGMII_FER_TBI (int) ; 

__attribute__((used)) static inline u32 rgmii_mode_mask(int mode, int input)
{
	switch (mode) {
	case PHY_MODE_RGMII:
		return RGMII_FER_RGMII(input);
	case PHY_MODE_TBI:
		return RGMII_FER_TBI(input);
	case PHY_MODE_GMII:
		return RGMII_FER_GMII(input);
	case PHY_MODE_MII:
		return RGMII_FER_MII(input);
	case PHY_MODE_RTBI:
		return RGMII_FER_RTBI(input);
	default:
		BUG();
	}
}