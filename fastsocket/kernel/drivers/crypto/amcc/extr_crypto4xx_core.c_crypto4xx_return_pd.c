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
typedef  int /*<<< orphan*/  u32 ;
struct pd_uinfo {int /*<<< orphan*/  state; } ;
struct crypto4xx_device {int /*<<< orphan*/  pdr_head; } ;
struct TYPE_4__ {scalar_t__ w; } ;
struct TYPE_3__ {scalar_t__ w; } ;
struct ce_pd {TYPE_2__ pd_ctl_len; TYPE_1__ pd_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PD_ENTRY_FREE ; 

void crypto4xx_return_pd(struct crypto4xx_device *dev,
			 u32 pd_entry, struct ce_pd *pd,
			 struct pd_uinfo *pd_uinfo)
{
	/* irq should be already disabled */
	dev->pdr_head = pd_entry;
	pd->pd_ctl.w = 0;
	pd->pd_ctl_len.w = 0;
	pd_uinfo->state = PD_ENTRY_FREE;
}