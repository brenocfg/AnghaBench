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
struct TYPE_2__ {int /*<<< orphan*/  resource_allocation_enable_RW; int /*<<< orphan*/  resource_allocation_groupID_RW; } ;
struct spu_state {TYPE_1__ priv1; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spu_resource_allocation_enable_get (struct spu*) ; 
 int /*<<< orphan*/  spu_resource_allocation_groupID_get (struct spu*) ; 

__attribute__((used)) static inline void save_mfc_rag(struct spu_state *csa, struct spu *spu)
{
	/* Save, Step 38:
	 *     Save RA_GROUP_ID register and the
	 *     RA_ENABLE reigster in the CSA.
	 */
	csa->priv1.resource_allocation_groupID_RW =
		spu_resource_allocation_groupID_get(spu);
	csa->priv1.resource_allocation_enable_RW =
		spu_resource_allocation_enable_get(spu);
}