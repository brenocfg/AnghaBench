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
struct sky2_hw {int flags; } ;

/* Variables and functions */
 int SKY2_HW_FIBRE_PHY ; 

__attribute__((used)) static inline int sky2_is_copper(const struct sky2_hw *hw)
{
	return !(hw->flags & SKY2_HW_FIBRE_PHY);
}