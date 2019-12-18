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
typedef  int u16 ;
struct skge_hw {scalar_t__ chip_id; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_GENESIS ; 
 int GMR_FS_LEN_SHIFT ; 
 int XMR_FS_LEN_SHIFT ; 

__attribute__((used)) static inline u16 phy_length(const struct skge_hw *hw, u32 status)
{
	if (hw->chip_id == CHIP_ID_GENESIS)
		return status >> XMR_FS_LEN_SHIFT;
	else
		return status >> GMR_FS_LEN_SHIFT;
}