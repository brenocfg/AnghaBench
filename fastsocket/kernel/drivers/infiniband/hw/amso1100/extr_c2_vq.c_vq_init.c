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
struct TYPE_2__ {int /*<<< orphan*/  msg_size; } ;
struct c2_dev {int /*<<< orphan*/ * host_msg_cache; TYPE_1__ rep_vq; int /*<<< orphan*/  vq_cache_name; scalar_t__ devnum; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/ * kmem_cache_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char) ; 

int vq_init(struct c2_dev *c2dev)
{
	sprintf(c2dev->vq_cache_name, "c2-vq:dev%c",
		(char) ('0' + c2dev->devnum));
	c2dev->host_msg_cache =
	    kmem_cache_create(c2dev->vq_cache_name, c2dev->rep_vq.msg_size, 0,
			      SLAB_HWCACHE_ALIGN, NULL);
	if (c2dev->host_msg_cache == NULL) {
		return -ENOMEM;
	}
	return 0;
}