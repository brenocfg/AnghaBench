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
struct vhost_virtqueue {int dummy; } ;
struct vhost_ubuf_ref {struct vhost_virtqueue* vq; int /*<<< orphan*/  wait; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct vhost_ubuf_ref* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct vhost_ubuf_ref* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

struct vhost_ubuf_ref *vhost_ubuf_alloc(struct vhost_virtqueue *vq,
					bool zcopy)
{
	struct vhost_ubuf_ref *ubufs;
	/* No zero copy backend? Nothing to count. */
	if (!zcopy)
		return NULL;
	ubufs = kmalloc(sizeof *ubufs, GFP_KERNEL);
	if (!ubufs)
		return ERR_PTR(-ENOMEM);
	kref_init(&ubufs->kref);
	init_waitqueue_head(&ubufs->wait);
	ubufs->vq = vq;
	return ubufs;
}