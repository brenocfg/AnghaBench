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
struct vhost_memory {int dummy; } ;
struct vhost_dev {int nvqs; TYPE_1__* vqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  log_base; scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vq_memory_access_ok (int /*<<< orphan*/ ,struct vhost_memory*,int) ; 

__attribute__((used)) static int memory_access_ok(struct vhost_dev *d, struct vhost_memory *mem,
			    int log_all)
{
	int i;
	for (i = 0; i < d->nvqs; ++i) {
		int ok;
		mutex_lock(&d->vqs[i].mutex);
		/* If ring is inactive, will check when it's enabled. */
		if (d->vqs[i].private_data)
			ok = vq_memory_access_ok(d->vqs[i].log_base, mem,
						 log_all);
		else
			ok = 1;
		mutex_unlock(&d->vqs[i].mutex);
		if (!ok)
			return 0;
	}
	return 1;
}