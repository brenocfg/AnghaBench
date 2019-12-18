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
struct mthca_ah {TYPE_1__* av; } ;
struct TYPE_2__ {int g_slid; } ;

/* Variables and functions */

int mthca_ah_grh_present(struct mthca_ah *ah)
{
	return !!(ah->av->g_slid & 0x80);
}