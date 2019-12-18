#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pd_uinfo {scalar_t__ state; } ;
struct device {int dummy; } ;
struct crypto4xx_core_device {TYPE_3__* dev; } ;
struct TYPE_5__ {scalar_t__ pe_done; int /*<<< orphan*/  host_ready; } ;
struct TYPE_6__ {TYPE_1__ bf; } ;
struct ce_pd {TYPE_2__ pd_ctl; } ;
struct TYPE_7__ {scalar_t__ pdr_head; scalar_t__ pdr_tail; struct ce_pd* pdr; struct pd_uinfo* pdr_uinfo; } ;

/* Variables and functions */
 scalar_t__ PD_ENTRY_FREE ; 
 scalar_t__ PD_ENTRY_INUSE ; 
 int /*<<< orphan*/  crypto4xx_pd_done (TYPE_3__*,int) ; 
 int /*<<< orphan*/  crypto4xx_put_pd_to_pdr (TYPE_3__*,int) ; 
 struct crypto4xx_core_device* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void crypto4xx_bh_tasklet_cb(unsigned long data)
{
	struct device *dev = (struct device *)data;
	struct crypto4xx_core_device *core_dev = dev_get_drvdata(dev);
	struct pd_uinfo *pd_uinfo;
	struct ce_pd *pd;
	u32 tail;

	while (core_dev->dev->pdr_head != core_dev->dev->pdr_tail) {
		tail = core_dev->dev->pdr_tail;
		pd_uinfo = core_dev->dev->pdr_uinfo +
			sizeof(struct pd_uinfo)*tail;
		pd =  core_dev->dev->pdr + sizeof(struct ce_pd) * tail;
		if ((pd_uinfo->state == PD_ENTRY_INUSE) &&
				   pd->pd_ctl.bf.pe_done &&
				   !pd->pd_ctl.bf.host_ready) {
			pd->pd_ctl.bf.pe_done = 0;
			crypto4xx_pd_done(core_dev->dev, tail);
			crypto4xx_put_pd_to_pdr(core_dev->dev, tail);
			pd_uinfo->state = PD_ENTRY_FREE;
		} else {
			/* if tail not done, break */
			break;
		}
	}
}