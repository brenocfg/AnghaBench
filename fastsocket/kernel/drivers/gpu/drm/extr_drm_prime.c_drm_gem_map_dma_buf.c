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
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct drm_gem_object {TYPE_3__* dev; } ;
struct dma_buf_attachment {int /*<<< orphan*/  dev; TYPE_1__* dmabuf; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; TYPE_2__* driver; } ;
struct TYPE_5__ {struct sg_table* (* gem_prime_get_sg_table ) (struct drm_gem_object*) ;} ;
struct TYPE_4__ {struct drm_gem_object* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct sg_table*) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sg_table* stub1 (struct drm_gem_object*) ; 

__attribute__((used)) static struct sg_table *drm_gem_map_dma_buf(struct dma_buf_attachment *attach,
		enum dma_data_direction dir)
{
	struct drm_gem_object *obj = attach->dmabuf->priv;
	struct sg_table *sgt;

	mutex_lock(&obj->dev->struct_mutex);

	sgt = obj->dev->driver->gem_prime_get_sg_table(obj);

	if (!IS_ERR_OR_NULL(sgt))
		dma_map_sg(attach->dev, sgt->sgl, sgt->nents, dir);

	mutex_unlock(&obj->dev->struct_mutex);
	return sgt;
}