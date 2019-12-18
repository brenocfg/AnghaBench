#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scatterlist {int /*<<< orphan*/  length; int /*<<< orphan*/  dma_length; scalar_t__ dma_address; } ;
struct device {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 
 scalar_t__ sun4c_lockarea (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4c_get_scsi_sgl(struct device *dev, struct scatterlist *sg, int sz)
{
	while (sz != 0) {
		--sz;
		sg->dma_address = (__u32)sun4c_lockarea(sg_virt(sg), sg->length);
		sg->dma_length = sg->length;
		sg = sg_next(sg);
	}
}