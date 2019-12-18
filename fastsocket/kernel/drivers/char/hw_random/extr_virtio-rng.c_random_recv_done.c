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
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 unsigned int data_left ; 
 int /*<<< orphan*/  have_data ; 
 int /*<<< orphan*/  virtqueue_get_buf (struct virtqueue*,unsigned int*) ; 

__attribute__((used)) static void random_recv_done(struct virtqueue *vq)
{
	unsigned int len;

	/* We can get spurious callbacks, e.g. shared IRQs + virtio_pci. */
	if (!virtqueue_get_buf(vq, &len))
		return;

	data_left += len;
	complete(&have_data);
}