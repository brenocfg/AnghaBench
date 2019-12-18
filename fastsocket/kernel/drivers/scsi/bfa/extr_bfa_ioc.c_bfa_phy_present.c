#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_phy_s {TYPE_2__* ioc; } ;
typedef  int bfa_boolean_t ;
struct TYPE_4__ {TYPE_1__* attr; } ;
struct TYPE_3__ {scalar_t__ card_type; } ;

/* Variables and functions */
 scalar_t__ BFA_MFG_TYPE_LIGHTNING ; 

__attribute__((used)) static bfa_boolean_t
bfa_phy_present(struct bfa_phy_s *phy)
{
	return (phy->ioc->attr->card_type == BFA_MFG_TYPE_LIGHTNING);
}