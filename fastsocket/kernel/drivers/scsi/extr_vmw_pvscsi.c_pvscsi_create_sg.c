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
struct scatterlist {int dummy; } ;
struct pvscsi_ctx {TYPE_1__* sgl; } ;
struct PVSCSISGElement {scalar_t__ flags; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {struct PVSCSISGElement* sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int PVSCSI_MAX_NUM_SG_ENTRIES_PER_SEGMENT ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static void pvscsi_create_sg(struct pvscsi_ctx *ctx,
			     struct scatterlist *sg, unsigned count)
{
	unsigned i;
	struct PVSCSISGElement *sge;

	BUG_ON(count > PVSCSI_MAX_NUM_SG_ENTRIES_PER_SEGMENT);

	sge = &ctx->sgl->sge[0];
	for (i = 0; i < count; i++, sg++) {
		sge[i].addr   = sg_dma_address(sg);
		sge[i].length = sg_dma_len(sg);
		sge[i].flags  = 0;
	}
}