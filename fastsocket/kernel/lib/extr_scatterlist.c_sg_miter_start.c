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
struct sg_mapping_iter {unsigned int __nents; unsigned int __flags; scalar_t__ __offset; struct scatterlist* __sg; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 unsigned int SG_MITER_FROM_SG ; 
 unsigned int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memset (struct sg_mapping_iter*,int /*<<< orphan*/ ,int) ; 

void sg_miter_start(struct sg_mapping_iter *miter, struct scatterlist *sgl,
		    unsigned int nents, unsigned int flags)
{
	memset(miter, 0, sizeof(struct sg_mapping_iter));

	miter->__sg = sgl;
	miter->__nents = nents;
	miter->__offset = 0;
	WARN_ON(!(flags & (SG_MITER_TO_SG | SG_MITER_FROM_SG)));
	miter->__flags = flags;
}