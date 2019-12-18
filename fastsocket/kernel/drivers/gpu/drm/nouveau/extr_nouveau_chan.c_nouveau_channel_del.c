#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nouveau_object {int dummy; } ;
struct TYPE_7__ {TYPE_3__* buffer; int /*<<< orphan*/  vma; int /*<<< orphan*/  handle; } ;
struct nouveau_channel {TYPE_1__ push; int /*<<< orphan*/  handle; int /*<<< orphan*/  drm; scalar_t__ fence; int /*<<< orphan*/  cli; } ;
struct TYPE_9__ {scalar_t__ pin_refcnt; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* context_del ) (struct nouveau_channel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NVDRM_DEVICE ; 
 int /*<<< orphan*/  kfree (struct nouveau_channel*) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  nouveau_bo_unmap (TYPE_3__*) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (TYPE_3__*) ; 
 int /*<<< orphan*/  nouveau_bo_vma_del (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_channel_idle (struct nouveau_channel*) ; 
 TYPE_2__* nouveau_fence (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_object_del (struct nouveau_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nouveau_object* nv_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_channel*) ; 

void
nouveau_channel_del(struct nouveau_channel **pchan)
{
	struct nouveau_channel *chan = *pchan;
	if (chan) {
		struct nouveau_object *client = nv_object(chan->cli);
		if (chan->fence) {
			nouveau_channel_idle(chan);
			nouveau_fence(chan->drm)->context_del(chan);
		}
		nouveau_object_del(client, NVDRM_DEVICE, chan->handle);
		nouveau_object_del(client, NVDRM_DEVICE, chan->push.handle);
		nouveau_bo_vma_del(chan->push.buffer, &chan->push.vma);
		nouveau_bo_unmap(chan->push.buffer);
		if (chan->push.buffer && chan->push.buffer->pin_refcnt)
			nouveau_bo_unpin(chan->push.buffer);
		nouveau_bo_ref(NULL, &chan->push.buffer);
		kfree(chan);
	}
	*pchan = NULL;
}