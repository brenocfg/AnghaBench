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
struct skge_hw {scalar_t__ chip_id; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_GENESIS ; 

__attribute__((used)) static inline u32 hwkhz(const struct skge_hw *hw)
{
	return (hw->chip_id == CHIP_ID_GENESIS) ? 53125 : 78125;
}