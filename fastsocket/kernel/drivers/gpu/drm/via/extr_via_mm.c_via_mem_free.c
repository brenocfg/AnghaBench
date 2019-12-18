#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct via_memblock {int /*<<< orphan*/  mm_node; int /*<<< orphan*/  owner_list; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_1__* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  object_idr; } ;
typedef  TYPE_1__ drm_via_private_t ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ drm_via_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 struct via_memblock* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct via_memblock*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int via_mem_free(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_via_private_t *dev_priv = dev->dev_private;
	drm_via_mem_t *mem = data;
	struct via_memblock *obj;

	mutex_lock(&dev->struct_mutex);
	obj = idr_find(&dev_priv->object_idr, mem->index);
	if (obj == NULL) {
		mutex_unlock(&dev->struct_mutex);
		return -EINVAL;
	}

	idr_remove(&dev_priv->object_idr, mem->index);
	list_del(&obj->owner_list);
	drm_mm_remove_node(&obj->mm_node);
	kfree(obj);
	mutex_unlock(&dev->struct_mutex);

	DRM_DEBUG("free = 0x%lx\n", mem->index);

	return 0;
}