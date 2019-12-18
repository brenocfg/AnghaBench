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
struct scatterlist {int /*<<< orphan*/  length; scalar_t__ dma_address; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sun4c_unlockarea (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4c_release_scsi_sgl(struct device *dev, struct scatterlist *sg, int sz)
{
	while (sz != 0) {
		--sz;
		sun4c_unlockarea((char *)sg->dma_address, sg->length);
		sg = sg_next(sg);
	}
}