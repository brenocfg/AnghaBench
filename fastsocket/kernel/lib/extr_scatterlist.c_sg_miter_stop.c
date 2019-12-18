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
struct sg_mapping_iter {scalar_t__ consumed; scalar_t__ length; int __flags; int /*<<< orphan*/ * addr; int /*<<< orphan*/ * page; int /*<<< orphan*/  __offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_BIO_SRC_IRQ ; 
 int SG_MITER_ATOMIC ; 
 int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  flush_kernel_dcache_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sg_miter_stop(struct sg_mapping_iter *miter)
{
	WARN_ON(miter->consumed > miter->length);

	/* drop resources from the last iteration */
	if (miter->addr) {
		miter->__offset += miter->consumed;

		if (miter->__flags & SG_MITER_TO_SG)
			flush_kernel_dcache_page(miter->page);

		if (miter->__flags & SG_MITER_ATOMIC) {
			WARN_ON(!irqs_disabled());
			kunmap_atomic(miter->addr, KM_BIO_SRC_IRQ);
		} else
			kunmap(miter->page);

		miter->page = NULL;
		miter->addr = NULL;
		miter->length = 0;
		miter->consumed = 0;
	}
}