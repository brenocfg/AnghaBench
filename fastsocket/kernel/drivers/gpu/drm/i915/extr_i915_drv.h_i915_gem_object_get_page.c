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
struct page {int dummy; } ;
struct drm_i915_gem_object {TYPE_1__* pages; } ;
struct TYPE_2__ {int nents; struct scatterlist* sgl; } ;

/* Variables and functions */
 int SG_MAX_SINGLE_ALLOC ; 
 struct scatterlist* sg_chain_ptr (struct scatterlist*) ; 
 struct page* sg_page (struct scatterlist*) ; 

__attribute__((used)) static inline struct page *i915_gem_object_get_page(struct drm_i915_gem_object *obj, int n)
{
	struct scatterlist *sg = obj->pages->sgl;
	int nents = obj->pages->nents;
	while (nents > SG_MAX_SINGLE_ALLOC) {
		if (n < SG_MAX_SINGLE_ALLOC - 1)
			break;

		sg = sg_chain_ptr(sg + SG_MAX_SINGLE_ALLOC - 1);
		n -= SG_MAX_SINGLE_ALLOC - 1;
		nents -= SG_MAX_SINGLE_ALLOC - 1;
	}
	return sg_page(sg+n);
}