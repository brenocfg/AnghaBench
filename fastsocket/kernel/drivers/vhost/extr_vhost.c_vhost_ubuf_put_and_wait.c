#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct vhost_ubuf_ref {TYPE_1__ kref; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vhost_ubuf_ref*) ; 
 int /*<<< orphan*/  kref_put (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_zerocopy_done_signal ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void vhost_ubuf_put_and_wait(struct vhost_ubuf_ref *ubufs)
{
	kref_put(&ubufs->kref, vhost_zerocopy_done_signal);
	wait_event(ubufs->wait, !atomic_read(&ubufs->kref.refcount));
	kfree(ubufs);
}