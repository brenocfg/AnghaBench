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
struct lem_counter {int lem_float_ber; } ;
struct s_phy {TYPE_1__* mib; struct lem_counter lem; } ;
struct TYPE_2__ {int fddiPORTLer_Estimate; } ;

/* Variables and functions */

__attribute__((used)) static void reset_lem_struct(struct s_phy *phy)
{
	struct lem_counter *lem = &phy->lem ;

	phy->mib->fddiPORTLer_Estimate = 15 ;
	lem->lem_float_ber = 15 * 100 ;
}