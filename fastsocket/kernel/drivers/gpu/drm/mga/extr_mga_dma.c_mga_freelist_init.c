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
struct drm_device_dma {int buf_count; struct drm_buf** buflist; } ;
struct drm_device {struct drm_device_dma* dma; } ;
struct drm_buf {TYPE_3__* dev_private; } ;
struct TYPE_5__ {TYPE_2__* head; TYPE_2__* tail; } ;
typedef  TYPE_1__ drm_mga_private_t ;
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* prev; struct drm_buf* buf; int /*<<< orphan*/  age; } ;
typedef  TYPE_2__ drm_mga_freelist_t ;
struct TYPE_7__ {scalar_t__ dispatched; scalar_t__ discard; TYPE_2__* list_entry; } ;
typedef  TYPE_3__ drm_mga_buf_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MGA_BUFFER_FREE ; 
 int /*<<< orphan*/  MGA_BUFFER_USED ; 
 int /*<<< orphan*/  SET_AGE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mga_freelist_init(struct drm_device *dev, drm_mga_private_t *dev_priv)
{
	struct drm_device_dma *dma = dev->dma;
	struct drm_buf *buf;
	drm_mga_buf_priv_t *buf_priv;
	drm_mga_freelist_t *entry;
	int i;
	DRM_DEBUG("count=%d\n", dma->buf_count);

	dev_priv->head = kzalloc(sizeof(drm_mga_freelist_t), GFP_KERNEL);
	if (dev_priv->head == NULL)
		return -ENOMEM;

	SET_AGE(&dev_priv->head->age, MGA_BUFFER_USED, 0);

	for (i = 0; i < dma->buf_count; i++) {
		buf = dma->buflist[i];
		buf_priv = buf->dev_private;

		entry = kzalloc(sizeof(drm_mga_freelist_t), GFP_KERNEL);
		if (entry == NULL)
			return -ENOMEM;

		entry->next = dev_priv->head->next;
		entry->prev = dev_priv->head;
		SET_AGE(&entry->age, MGA_BUFFER_FREE, 0);
		entry->buf = buf;

		if (dev_priv->head->next != NULL)
			dev_priv->head->next->prev = entry;
		if (entry->next == NULL)
			dev_priv->tail = entry;

		buf_priv->list_entry = entry;
		buf_priv->discard = 0;
		buf_priv->dispatched = 0;

		dev_priv->head->next = entry;
	}

	return 0;
}