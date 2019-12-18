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
struct TYPE_2__ {scalar_t__ mode; } ;
struct bonding {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ BOND_MODE_ALB ; 
 scalar_t__ BOND_MODE_TLB ; 

__attribute__((used)) static inline bool bond_is_lb(const struct bonding *bond)
{
	return bond->params.mode == BOND_MODE_TLB
		|| bond->params.mode == BOND_MODE_ALB;
}