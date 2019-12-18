#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long start; } ;
struct via_memblock {TYPE_3__ mm_node; int /*<<< orphan*/  owner_list; } ;
struct via_file_private {int /*<<< orphan*/  obj_list; } ;
struct drm_file {struct via_file_private* driver_priv; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; scalar_t__ dev_private; } ;
struct TYPE_5__ {scalar_t__ vram_initialized; scalar_t__ agp_initialized; scalar_t__ agp_offset; scalar_t__ vram_offset; int /*<<< orphan*/  object_idr; int /*<<< orphan*/  vram_mm; int /*<<< orphan*/  agp_mm; } ;
typedef  TYPE_1__ drm_via_private_t ;
struct TYPE_6__ {scalar_t__ type; unsigned long size; int index; scalar_t__ offset; } ;
typedef  TYPE_2__ drm_via_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VIA_MEM_AGP ; 
 scalar_t__ VIA_MEM_VIDEO ; 
 unsigned long VIA_MM_ALIGN_MASK ; 
 unsigned long VIA_MM_ALIGN_SHIFT ; 
 int drm_mm_insert_node (int /*<<< orphan*/ *,TYPE_3__*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_remove_node (TYPE_3__*) ; 
 int idr_get_new_above (int /*<<< orphan*/ *,struct via_memblock*,int,int*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct via_memblock*) ; 
 struct via_memblock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int via_mem_alloc(struct drm_device *dev, void *data,
		  struct drm_file *file)
{
	drm_via_mem_t *mem = data;
	int retval = 0, user_key;
	struct via_memblock *item;
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;
	struct via_file_private *file_priv = file->driver_priv;
	unsigned long tmpSize;

	if (mem->type > VIA_MEM_AGP) {
		DRM_ERROR("Unknown memory type allocation\n");
		return -EINVAL;
	}
	mutex_lock(&dev->struct_mutex);
	if (0 == ((mem->type == VIA_MEM_VIDEO) ? dev_priv->vram_initialized :
		      dev_priv->agp_initialized)) {
		DRM_ERROR
		    ("Attempt to allocate from uninitialized memory manager.\n");
		mutex_unlock(&dev->struct_mutex);
		return -EINVAL;
	}

	item = kzalloc(sizeof(*item), GFP_KERNEL);
	if (!item) {
		retval = -ENOMEM;
		goto fail_alloc;
	}

	tmpSize = (mem->size + VIA_MM_ALIGN_MASK) >> VIA_MM_ALIGN_SHIFT;
	if (mem->type == VIA_MEM_AGP)
		retval = drm_mm_insert_node(&dev_priv->agp_mm,
					    &item->mm_node,
					    tmpSize, 0);
	else
		retval = drm_mm_insert_node(&dev_priv->vram_mm,
					    &item->mm_node,
					    tmpSize, 0);
	if (retval)
		goto fail_alloc;

again:
	if (idr_pre_get(&dev_priv->object_idr, GFP_KERNEL) == 0) {
		retval = -ENOMEM;
		goto fail_idr;
	}

	retval = idr_get_new_above(&dev_priv->object_idr, item, 1, &user_key);
	if (retval == -EAGAIN)
		goto again;
	if (retval)
		goto fail_idr;

	list_add(&item->owner_list, &file_priv->obj_list);
	mutex_unlock(&dev->struct_mutex);

	mem->offset = ((mem->type == VIA_MEM_VIDEO) ?
		      dev_priv->vram_offset : dev_priv->agp_offset) +
	    ((item->mm_node.start) << VIA_MM_ALIGN_SHIFT);
	mem->index = user_key;

	return 0;

fail_idr:
	drm_mm_remove_node(&item->mm_node);
fail_alloc:
	kfree(item);
	mutex_unlock(&dev->struct_mutex);

	mem->offset = 0;
	mem->size = 0;
	mem->index = 0;
	DRM_DEBUG("Video memory allocation failed\n");

	return retval;
}