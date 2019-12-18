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
typedef  int /*<<< orphan*/  u32 ;
struct rds_iw_connection {TYPE_3__* i_mr; TYPE_2__* i_cm_id; scalar_t__ i_dma_local_lkey; } ;
struct TYPE_6__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 rds_iw_local_dma_lkey(struct rds_iw_connection *ic)
{
	return ic->i_dma_local_lkey ? ic->i_cm_id->device->local_dma_lkey : ic->i_mr->lkey;
}