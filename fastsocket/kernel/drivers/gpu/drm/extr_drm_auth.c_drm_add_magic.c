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
struct drm_master {int /*<<< orphan*/  magicfree; int /*<<< orphan*/  magiclist; TYPE_1__* minor; } ;
struct TYPE_4__ {unsigned long key; } ;
struct drm_magic_entry {int /*<<< orphan*/  head; TYPE_2__ hash_item; struct drm_file* priv; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
typedef  scalar_t__ drm_magic_t ;
struct TYPE_3__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_ht_insert_item (int /*<<< orphan*/ *,TYPE_2__*) ; 
 struct drm_magic_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_add_magic(struct drm_master *master, struct drm_file *priv,
			 drm_magic_t magic)
{
	struct drm_magic_entry *entry;
	struct drm_device *dev = master->minor->dev;
	DRM_DEBUG("%d\n", magic);

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;
	entry->priv = priv;
	entry->hash_item.key = (unsigned long)magic;
	mutex_lock(&dev->struct_mutex);
	drm_ht_insert_item(&master->magiclist, &entry->hash_item);
	list_add_tail(&entry->head, &master->magicfree);
	mutex_unlock(&dev->struct_mutex);

	return 0;
}