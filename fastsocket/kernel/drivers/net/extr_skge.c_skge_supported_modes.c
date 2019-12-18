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
typedef  int u32 ;
struct skge_hw {scalar_t__ chip_id; scalar_t__ copper; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_GENESIS ; 
 scalar_t__ CHIP_ID_YUKON ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_TP ; 

__attribute__((used)) static u32 skge_supported_modes(const struct skge_hw *hw)
{
	u32 supported;

	if (hw->copper) {
		supported = SUPPORTED_10baseT_Half
			| SUPPORTED_10baseT_Full
			| SUPPORTED_100baseT_Half
			| SUPPORTED_100baseT_Full
			| SUPPORTED_1000baseT_Half
			| SUPPORTED_1000baseT_Full
			| SUPPORTED_Autoneg| SUPPORTED_TP;

		if (hw->chip_id == CHIP_ID_GENESIS)
			supported &= ~(SUPPORTED_10baseT_Half
					     | SUPPORTED_10baseT_Full
					     | SUPPORTED_100baseT_Half
					     | SUPPORTED_100baseT_Full);

		else if (hw->chip_id == CHIP_ID_YUKON)
			supported &= ~SUPPORTED_1000baseT_Half;
	} else
		supported = SUPPORTED_1000baseT_Full | SUPPORTED_1000baseT_Half
			| SUPPORTED_FIBRE | SUPPORTED_Autoneg;

	return supported;
}