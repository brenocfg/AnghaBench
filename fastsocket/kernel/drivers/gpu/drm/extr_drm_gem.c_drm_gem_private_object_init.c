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
struct drm_gem_object {size_t size; int /*<<< orphan*/  handle_count; int /*<<< orphan*/  refcount; int /*<<< orphan*/ * filp; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

int drm_gem_private_object_init(struct drm_device *dev,
			struct drm_gem_object *obj, size_t size)
{
	BUG_ON((size & (PAGE_SIZE - 1)) != 0);

	obj->dev = dev;
	obj->filp = NULL;

	kref_init(&obj->refcount);
	atomic_set(&obj->handle_count, 0);
	obj->size = size;

	return 0;
}