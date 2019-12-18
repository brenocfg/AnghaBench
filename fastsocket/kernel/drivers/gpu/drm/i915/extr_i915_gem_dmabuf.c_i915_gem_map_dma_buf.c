#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int /*<<< orphan*/  nents; struct scatterlist* sgl; } ;
struct scatterlist {int dummy; } ;
struct TYPE_7__ {TYPE_4__* dev; } ;
struct drm_i915_gem_object {TYPE_3__ base; TYPE_2__* pages; } ;
struct dma_buf_attachment {int /*<<< orphan*/  dev; TYPE_1__* dmabuf; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_8__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_6__ {int nents; struct scatterlist* sgl; } ;
struct TYPE_5__ {struct drm_i915_gem_object* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct sg_table* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int i915_gem_object_get_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int i915_mutex_lock_interruptible (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 struct sg_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sg_alloc_table (struct sg_table*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sg_table *i915_gem_map_dma_buf(struct dma_buf_attachment *attachment,
					     enum dma_data_direction dir)
{
	struct drm_i915_gem_object *obj = attachment->dmabuf->priv;
	struct sg_table *st;
	struct scatterlist *src, *dst;
	int ret, i;

	ret = i915_mutex_lock_interruptible(obj->base.dev);
	if (ret)
		return ERR_PTR(ret);

	ret = i915_gem_object_get_pages(obj);
	if (ret) {
		st = ERR_PTR(ret);
		goto out;
	}

	/* Copy sg so that we make an independent mapping */
	st = kmalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (st == NULL) {
		st = ERR_PTR(-ENOMEM);
		goto out;
	}

	ret = sg_alloc_table(st, obj->pages->nents, GFP_KERNEL);
	if (ret) {
		kfree(st);
		st = ERR_PTR(ret);
		goto out;
	}

	src = obj->pages->sgl;
	dst = st->sgl;
	for (i = 0; i < obj->pages->nents; i++) {
		sg_set_page(dst, sg_page(src), PAGE_SIZE, 0);
		dst = sg_next(dst);
		src = sg_next(src);
	}

	if (!dma_map_sg(attachment->dev, st->sgl, st->nents, dir)) {
		sg_free_table(st);
		kfree(st);
		st = ERR_PTR(-ENOMEM);
		goto out;
	}

	i915_gem_object_pin_pages(obj);

out:
	mutex_unlock(&obj->base.dev->struct_mutex);
	return st;
}