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
struct TYPE_3__ {int /*<<< orphan*/  inactive_list; } ;
struct drm_i915_private {TYPE_1__ mm; } ;
struct TYPE_4__ {int write_domain; struct drm_device* dev; } ;
struct drm_i915_gem_object {int fenced_gpu_access; TYPE_2__ base; scalar_t__ active; scalar_t__ last_fenced_seqno; scalar_t__ last_write_seqno; scalar_t__ last_read_seqno; int /*<<< orphan*/ * ring; int /*<<< orphan*/  ring_list; int /*<<< orphan*/  mm_list; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int I915_GEM_GPU_DOMAINS ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (TYPE_2__*) ; 
 int /*<<< orphan*/  i915_verify_lists (struct drm_device*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
i915_gem_object_move_to_inactive(struct drm_i915_gem_object *obj)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;

	BUG_ON(obj->base.write_domain & ~I915_GEM_GPU_DOMAINS);
	BUG_ON(!obj->active);

	list_move_tail(&obj->mm_list, &dev_priv->mm.inactive_list);

	list_del_init(&obj->ring_list);
	obj->ring = NULL;

	obj->last_read_seqno = 0;
	obj->last_write_seqno = 0;
	obj->base.write_domain = 0;

	obj->last_fenced_seqno = 0;
	obj->fenced_gpu_access = false;

	obj->active = 0;
	drm_gem_object_unreference(&obj->base);

	WARN_ON(i915_verify_lists(dev));
}