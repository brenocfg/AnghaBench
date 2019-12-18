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
struct bonding {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_MASTER_ALB ; 

__attribute__((used)) static inline void bond_set_master_alb_flags(struct bonding *bond)
{
	bond->dev->priv_flags |= IFF_MASTER_ALB;
}