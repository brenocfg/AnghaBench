#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mesh_rmc {int dummy; } ;
struct TYPE_4__ {TYPE_3__* rmc; } ;
struct TYPE_5__ {TYPE_1__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;
struct TYPE_6__ {int idx_mask; int /*<<< orphan*/ * bucket; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RMC_BUCKETS ; 
 TYPE_3__* kmalloc (int,int /*<<< orphan*/ ) ; 

int mesh_rmc_init(struct ieee80211_sub_if_data *sdata)
{
	int i;

	sdata->u.mesh.rmc = kmalloc(sizeof(struct mesh_rmc), GFP_KERNEL);
	if (!sdata->u.mesh.rmc)
		return -ENOMEM;
	sdata->u.mesh.rmc->idx_mask = RMC_BUCKETS - 1;
	for (i = 0; i < RMC_BUCKETS; i++)
		INIT_LIST_HEAD(&sdata->u.mesh.rmc->bucket[i]);
	return 0;
}