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
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtqueue_disable_cb (struct virtqueue*) ; 
 int /*<<< orphan*/  virtqueue_enable_cb (struct virtqueue*) ; 
 void* virtqueue_get_buf (struct virtqueue*,unsigned int*) ; 

__attribute__((used)) static void virtscsi_vq_done(struct virtqueue *vq, void (*fn)(void *buf))
{
	void *buf;
	unsigned int len;

	do {
		virtqueue_disable_cb(vq);
		while ((buf = virtqueue_get_buf(vq, &len)) != NULL)
			fn(buf);
	} while (!virtqueue_enable_cb(vq));
}